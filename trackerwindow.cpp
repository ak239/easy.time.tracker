#include "trackerwindow.h"
#include "ui_trackerwindow.h"

#include "currentwindow.h"
#include "typedialog.h"
#include "autotypedialog.h"
#include "ltypesdialog.h"
#include "awayactiondialog.h"
#include "addautotypedialog.h"

#include <QtSql/QtSql>
#include <QMessageBox>

TrackerWindow::TrackerWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::TrackerWindow),
    model_(new QSqlTableModel(this)),
    perTypeModel_(new QSqlTableModel(this))
{
    ui->setupUi(this);

    model_->setTable("total_time_by_id_and_title");

    model_->setHeaderData(0, Qt::Horizontal, tr("Process ID"));
    model_->setHeaderData(1, Qt::Horizontal, tr("Window Title"));
    model_->setHeaderData(2, Qt::Horizontal, tr("EXE"));
    model_->setHeaderData(3, Qt::Horizontal, tr("Total Time(min)"));
    model_->setHeaderData(4, Qt::Horizontal, tr("Total Time(%)"));

    ui->tableView->setModel(model_);
    ui->tableView->setSortingEnabled(true);

    perTypeModel_->setTable("total_time_by_type");
    perTypeModel_->setHeaderData(0, Qt::Horizontal, tr("Type Name"));
    perTypeModel_->setHeaderData(1, Qt::Horizontal, tr("Total(time)"));
    perTypeModel_->setHeaderData(2, Qt::Horizontal, tr("Total(%)"));
    ui->tvSummary->setModel(perTypeModel_);
    ui->tvSummary->setSortingEnabled(true);
    perTypeModel_->select();
}

TrackerWindow::~TrackerWindow()
{
    delete ui;
}

void TrackerWindow::windowChanged()
{
    //model_->select();
    perTypeModel_->select();
}

void TrackerWindow::on_actionAutoTypes_triggered()
{
    AutoTypeDialog().exec();
}

void TrackerWindow::on_actionTypes_triggered()
{
    TypesDialog().exec();
}

void TrackerWindow::on_actionSetType_triggered()
{
    TypeDialog td;
    if (td.exec() == QDialog::Accepted)
    {
        QModelIndexList indexes = ui->tableView->selectionModel()->selectedRows();
        QSqlQuery query;
        query.prepare("UPDATE record SET type_id = :type_id WHERE process_id = :process_id AND title = :title AND module_name = :module_name");
        for (const QModelIndex& idx : indexes)
        {
            query.bindValue(":type_id",     td.type());
            query.bindValue(":process_id",  model_->data(model_->index(idx.row(), 0)));
            query.bindValue(":title",       model_->data(model_->index(idx.row(), 1)));
            query.bindValue(":module_name", model_->data(model_->index(idx.row(), 2)));
            query.exec();
        }
    }
    perTypeModel_->select();
    model_->select();
}

void TrackerWindow::on_actionRefresh_triggered()
{
    model_->select();
}

void TrackerWindow::on_actionAway_Action_triggered()
{
    AwayActionDialog().exec();
}

void TrackerWindow::on_actionGenerate_Auto_Type_triggered()
{
    QModelIndexList indexes = ui->tableView->selectionModel()->selectedRows();
    for (const QModelIndex& idx : indexes)
    {
        AddAutoTypeDialog d;
        d.setProcessID(model_->data(model_->index(idx.row(), 0)));
        d.setModuleName(model_->data(model_->index(idx.row(), 2)));
        d.setTitle(model_->data(model_->index(idx.row(), 1)));

        if (d.exec() == QDialog::Accepted)
        {
            QSqlQuery q;
            q.prepare("INSERT INTO auto_type (process_id, module_name, title, type_id, priority) VALUES "
                      "(:process_id, :module_name, :title, :type_id, :priority)");
            q.bindValue(":process_id",  d.processID());
            q.bindValue(":module_name", d.moduleName());
            q.bindValue(":title",       d.title());
            q.bindValue(":type_id",     d.typeID());
            q.bindValue(":priority",    d.priority());
            q.exec();

            q.prepare("UPDATE record SET type_id = :type_id WHERE process_id = :process_id AND title = :title AND module_name = :module_name");
            q.bindValue(":type_id",     d.typeID());
            q.bindValue(":process_id",  model_->data(model_->index(idx.row(), 0)));
            q.bindValue(":title",       model_->data(model_->index(idx.row(), 1)));
            q.bindValue(":module_name", model_->data(model_->index(idx.row(), 2)));
            q.exec();

            model_->select();
        }
    }
}
