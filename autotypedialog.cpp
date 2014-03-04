#include "autotypedialog.h"
#include "ui_autotypedialog.h"

#include <QtSql/QtSql>

#include "addautotypedialog.h"

const int PROCESS_ID_COL = 0;
const int MODULE_NAME_COL = 1;
const int TITLE_COL = 2;
const int TYPE_ID_COL = 3;
const int PRIORITY_COL = 4;

AutoTypeDialog::AutoTypeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AutoTypeDialog),
    model_(new QSqlTableModel(this))
{
    ui->setupUi(this);

    model_->setTable("auto_type");

    ui->tvAutoType->setModel(model_);
    model_->select();
}

AutoTypeDialog::~AutoTypeDialog()
{
    delete ui;
}

void AutoTypeDialog::on_tbAdd_clicked()
{
    AddAutoTypeDialog d;
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

        model_->select();
    }
}

void AutoTypeDialog::on_tbDel_clicked()
{
    QModelIndexList indexes = ui->tvAutoType->selectionModel()->selectedRows();
    QSqlQuery q;
    for (const QModelIndex& idx : indexes)
    {
        QVariant processID  = model_->data(model_->index(idx.row(), PROCESS_ID_COL));
        QVariant moduleName = model_->data(model_->index(idx.row(), MODULE_NAME_COL));
        QVariant title      = model_->data(model_->index(idx.row(), TITLE_COL));
        QVariant typeID     = model_->data(model_->index(idx.row(), TYPE_ID_COL));

        q.prepare(QString("DELETE FROM auto_type WHERE ") +
                  (processID.isNull()  ? "process_id is null AND " : "process_id = :process_id AND ") +
                  (moduleName.isNull() ? "module_name is null AND " : "module_name = :module_name AND ") +
                  (title.isNull() ? "title is null AND " : "title = :title AND ") +
                  "type_id = :type_id");

        q.bindValue(":process_id",  processID);
        q.bindValue(":module_name", moduleName);
        q.bindValue(":title",   title);
        q.bindValue(":type_id", typeID);
        q.exec();
    }
    model_->select();
}
