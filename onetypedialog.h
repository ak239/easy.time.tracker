#ifndef ONETYPEDIALOG_H
#define ONETYPEDIALOG_H

#include <QDialog>
#include <QVariant>

namespace Ui {
class OneTypeDialog;
}

class OneTypeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit OneTypeDialog(QWidget *parent = 0);
    ~OneTypeDialog();

    void setType(const QVariant& typeID);
    void setName(const QString& _name);

    QVariant typeID();
    QString  name();

private:
    Ui::OneTypeDialog *ui;
};

#endif // ONETYPEDIALOG_H
