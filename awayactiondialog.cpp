#include "awayactiondialog.h"
#include "ui_awayactiondialog.h"

#include <QTimer>
#include <QtSql/QtSql>

AwayActionDialog::AwayActionDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AwayActionDialog),
    timer_(new QTimer(this))
{
    ui->setupUi(this);

    timer_->setInterval(1000);
    timer_->setSingleShot(true);
    connect(timer_, &QTimer::timeout, this, &AwayActionDialog::changedTimeout);
}

AwayActionDialog::~AwayActionDialog()
{
    delete ui;
}

void AwayActionDialog::on_leAction_textChanged(const QString &arg1)
{
    Q_UNUSED(arg1)
    timer_->stop();
    timer_->start();
}

void AwayActionDialog::changedTimeout()
{
    setWindowTitle(ui->leAction->text());
}
