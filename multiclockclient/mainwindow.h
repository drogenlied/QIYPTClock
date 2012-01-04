#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include "signalhelper.h"
#include "multibroadcastclient.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void createClock(SignalHelper*);

private:
    Ui::MainWindow *ui;
    QGridLayout *grid;
    MultiBroadcastClient *m;
    int elementNr;
};

#endif // MAINWINDOW_H
