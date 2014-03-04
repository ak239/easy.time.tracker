#ifndef AUTOTYPEDIALOG_H
#define AUTOTYPEDIALOG_H

#include <QDialog>

class QSqlTableModel;

namespace Ui {
class AutoTypeDialog;
}

class AutoTypeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AutoTypeDialog(QWidget *parent = 0);
    ~AutoTypeDialog();

private slots:
    void on_tbAdd_clicked();
    void on_tbDel_clicked();

private:
    Ui::AutoTypeDialog *ui;
    QSqlTableModel* model_;
};

#endif // AUTOTYPEDIALOG_H
