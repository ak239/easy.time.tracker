#ifndef TYPEDIALOG_H
#define TYPEDIALOG_H

#include <QDialog>

namespace Ui {
class TypeDialog;
}

class QSqlTableModel;

class TypeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit TypeDialog(QWidget *parent = 0);
    ~TypeDialog();

    int type();

private:
    Ui::TypeDialog *ui;
    QSqlTableModel* model_;
};

#endif // TYPEDIALOG_H
