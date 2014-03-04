#include "onetypedialog.h"
#include "ui_onetypedialog.h"

OneTypeDialog::OneTypeDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::OneTypeDialog)
{
    ui->setupUi(this);
}

OneTypeDialog::~OneTypeDialog()
{
    delete ui;
}

void OneTypeDialog::setType(const QVariant &typeID)
{
    ui->leTypeID->setText(typeID.isNull() ? "" : QString::number(typeID.toInt()));
}

void OneTypeDialog::setName(const QString &_name)
{
    ui->leName->setText(_name);
}

QVariant OneTypeDialog::typeID()
{
    bool isOk = false;
    int val = ui->leTypeID->text().toInt(&isOk);
    return isOk ? val : QVariant();
}

QString OneTypeDialog::name()
{
    return ui->leName->text();
}
