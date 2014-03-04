#ifndef TRACKERWINDOW_H
#define TRACKERWINDOW_H

#include <QMainWindow>

namespace Ui {
class TrackerWindow;
}

class QSqlTableModel;

class TrackerWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit TrackerWindow(QWidget *parent = 0);
    ~TrackerWindow();

public slots:
    void windowChanged();

private slots:
    void on_actionAutoTypes_triggered();
    void on_actionTypes_triggered();
    void on_actionSetType_triggered();

    void on_actionRefresh_triggered();

private:
    QSqlTableModel* model_;
    QSqlTableModel* perTypeModel_;
    Ui::TrackerWindow *ui;
};

#endif // TRACKERWINDOW_H
