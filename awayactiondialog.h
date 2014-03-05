#ifndef AWAYACTIONDIALOG_H
#define AWAYACTIONDIALOG_H

#include <QDialog>

class QTimer;

namespace Ui {
class AwayActionDialog;
}

class AwayActionDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AwayActionDialog(QWidget *parent = 0);
    ~AwayActionDialog();

private slots:
    void on_leAction_textChanged(const QString &arg1);
    void changedTimeout();

private:
    Ui::AwayActionDialog *ui;
    QTimer* timer_;
};

#endif // AWAYACTIONDIALOG_H
