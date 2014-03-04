#include "addautotypedialog.h"
#include "ui_addautotypedialog.h"

#include <QSqlTableModel>
#include <QSqlRecord>

AddAutoTypeDialog::AddAutoTypeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddAutoTypeDialog),
    model_(new QSqlTableModel(this))
{
    ui->setupUi(this);

    model_->setTable("type");
    ui->cbType->setModel(model_);
    ui->cbType->setModelColumn(1);

    model_->select();

    ui->cbType->setCurrentIndex(0);
}

AddAutoTypeDialog::~AddAutoTypeDialog()
{
    delete ui;
}

QVariant AddAutoTypeDialog::processID() const
{
    bool isOk = false;
    int val = ui->leProcessID->text().toInt(&isOk);
    return isOk ? val : QVariant();
}

QVariant AddAutoTypeDialog::moduleName() const
{
    return ui->leModuleName->text().isEmpty() ? QVariant() : ui->leModuleName->text();
}

QVariant AddAutoTypeDialog::title() const
{
    return ui->leTitle->text().isEmpty() ? QVariant() : ui->leTitle->text();
}

int AddAutoTypeDialog::typeID() const
{
    return model_->record(ui->cbType->currentIndex()).value("id").toInt();
}

int AddAutoTypeDialog::priority() const
{
    return ui->sbPriority->value();
}
