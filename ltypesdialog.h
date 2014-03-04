#ifndef LTYPESDIALOG_H
#define LTYPESDIALOG_H

#include <QDialog>

namespace Ui {
class lTypesDialog;
}

class QSqlTableModel;

class TypesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TypesDialog(QWidget *parent = 0);
    ~TypesDialog();

private slots:
    void on_tbAdd_clicked();

    void on_tbUpd_clicked();

private:
    Ui::lTypesDialog *ui;
    QSqlTableModel* model_;
};

#endif // LTYPESDIALOG_H
