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

void AddAutoTypeDialog::setProcessID(const QVariant &_processID)
{
    ui->leProcessID->setText(_processID.isNull() ? "" : _processID.toString());
}

void AddAutoTypeDialog::setModuleName(const QVariant &_moduleName)
{
    ui->leModuleName->setText(_moduleName.isNull() ? "" : _moduleName.toString());
}

void AddAutoTypeDialog::setTitle(const QVariant &_title)
{
    ui->leTitle->setText(_title.isNull() ? "" : _title.toString());
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
