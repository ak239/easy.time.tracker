#include "trackerwindow.h"
#include <QApplication>
#include <QTimer>

#include <QtSql/QtSql>
#include <QMessageBox>

#include "currentwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("track.db");
    if (!db.open())
    {
        QMessageBox::critical(nullptr, QObject::tr("Ошибка"),
                              QObject::tr("Не могу открыть БД. Ошибка: %1").arg(db.lastError().databaseText()));
        return -1;
    }

    TrackerWindow w;
    w.show();

    CurrentWindow wnd;
    QTimer timer;
    timer.setInterval(500);
    QObject::connect(&timer, &QTimer::timeout, &wnd, &CurrentWindow::check);
    QObject::connect(&wnd, &CurrentWindow::changed, &w, &TrackerWindow::windowChanged);

    timer.start();

    return a.exec();
}
