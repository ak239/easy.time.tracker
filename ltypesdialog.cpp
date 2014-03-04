#include "ltypesdialog.h"
#include "ui_ltypesdialog.h"

#include <QtSql/QtSql>

#include "onetypedialog.h"

TypesDialog::TypesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::lTypesDialog),
    model_(new QSqlTableModel(this))
{
    ui->setupUi(this);

    model_->setTable("type");
    ui->tvTypes->setModel(model_);
    model_->select();
}

TypesDialog::~TypesDialog()
{
    delete ui;
}

void TypesDialog::on_tbAdd_clicked()
{
    OneTypeDialog d;
    if (d.exec() == QDialog::Accepted)
    {
        QSqlQuery q;
        q.prepare("INSERT INTO type (name) VALUES (:name)");
        q.bindValue(":name", d.name());
        q.exec();
    }
    model_->select();
}

void TypesDialog::on_tbUpd_clicked()
{
    QModelIndexList indexes = ui->tvTypes->selectionModel()->selectedRows();
    QSqlQuery q;
    q.prepare("UPDATE type SET name = :name WHERE id = :id");
    for (const QModelIndex& idx : indexes)
    {
        OneTypeDialog d;

        QVariant typeID  = model_->data(model_->index(idx.row(), 0));
        d.setType(typeID);
        d.setName(model_->data(model_->index(idx.row(), 1)).toString());

        if (d.exec() == QDialog::Accepted)
        {
            q.bindValue(":id",   d.typeID());
            q.bindValue(":name", d.name());
            q.exec();
        }
    }
    model_->select();
}
