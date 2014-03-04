#include "typedialog.h"
#include "ui_typedialog.h"

#include <QSqlTableModel>
#include <QSqlRecord>

TypeDialog::TypeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::TypeDialog),
    model_(new QSqlTableModel(this))
{
    ui->setupUi(this);

    model_->setTable("type");
    ui->cbType->setModel(model_);
    ui->cbType->setModelColumn(1);

    model_->select();
}

TypeDialog::~TypeDialog()
{
    delete ui;
}

int TypeDialog::type()
{
    return model_->record(ui->cbType->currentIndex()).value("id").toInt();
}
