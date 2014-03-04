#include "currentwindow.h"
#include "Psapi.h"

#include <QtSql/QtSql>
#include <QDateTime>

CurrentWindow::CurrentWindow(QObject *parent) :
    QObject(parent), curWindow_(0), processID_(0), curRecID_(0)
{
}

QString CurrentWindow::title() const
{
    return title_;
}

int CurrentWindow::processID() const
{
    return processID_;
}

void CurrentWindow::check()
{
    HWND wnd = GetForegroundWindow();
    if (wnd == 0)
        return;

    wchar_t buf[1024];
    DWORD   len      = GetWindowTextW(wnd, buf, 1024);
    QString curTitle = QString::fromWCharArray(buf, len);

    if (wnd != curWindow_ || title_ != curTitle)
    {
        curWindow_ = wnd;

        title_ = curTitle;
        GetWindowThreadProcessId(wnd, &processID_);

        HANDLE processHandle = OpenProcess(PROCESS_QUERY_INFORMATION | PROCESS_VM_READ, FALSE, processID_);
        QString moduleName;
        if (processHandle != NULL)
        {
            DWORD   len      = GetModuleFileNameExW(processHandle, 0, buf, 1024);
            moduleName = QString::fromWCharArray(buf, len);
        }

        QSqlQuery query;
        query.prepare("SELECT type_id FROM auto_type WHERE process_id = :process_id OR title = :title OR module_name = :module_name ORDER BY priority DESC LIMIT 1");
        query.bindValue(":process_id",  processID());
        query.bindValue(":title",       title());
        query.bindValue(":module_name", moduleName);

        query.exec();

        QVariant typeID;
        if (query.next())
        {
             typeID = query.record().value("type_id");
        }

        query.prepare("INSERT INTO record (process_id, title, module_name, type_id) VALUES (:process_id, :title, :module_name, :type_id)");
        query.bindValue(":process_id",  processID());
        query.bindValue(":title",       title());
        query.bindValue(":module_name", moduleName);
        query.bindValue(":type_id",     typeID);

        query.exec();

        curRecID_ = query.lastInsertId().toInt();

        emit changed();
    }
    else if (curWindow_ != 0)
    {
        QSqlQuery query;
        query.prepare("UPDATE record SET last_active = :last_active WHERE id = :id");

        query.bindValue(":last_active", QDateTime::currentMSecsSinceEpoch());
        query.bindValue(":id", curRecID_);

        query.exec();

        emit changed();
    }
}
