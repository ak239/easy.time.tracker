#ifndef CURRENTWINDOW_H
#define CURRENTWINDOW_H

#include <QObject>
#include <QString>

#include <windows.h>
#undef min

class CurrentWindow : public QObject
{
    Q_OBJECT
public:
    explicit CurrentWindow(QObject *parent = 0);

    QString title() const;
    int processID() const;

public slots:
    void check();

signals:
    void changed();

private:
    HWND    curWindow_;
    QString title_;
    DWORD   processID_;
    int     curRecID_;
};

#endif // CURRENTWINDOW_H
