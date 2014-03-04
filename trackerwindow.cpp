#include "trackerwindow.h"
#include "ui_trackerwindow.h"

#include "currentwindow.h"
#include "typedialog.h"
#include "autotypedialog.h"
#include "ltypesdialog.h"

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
    ui->tvSummary->setModel(perTypeModel_);
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
