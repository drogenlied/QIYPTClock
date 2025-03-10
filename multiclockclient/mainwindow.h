#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGridLayout>
#include <QProgressBar>
#include <QTimer>
#include "signalhelper.h"
#include "multibroadcastclient.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(bool noairport, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void createClock(SignalHelper*);

private:
    Ui::MainWindow *ui;
    QGridLayout *grid;
    MultiBroadcastClient *m;
    int elementNr;
    QTimer *timer;
    bool airportMode;
};

class formatSetter : public QObject
{
    Q_OBJECT

public:
    explicit formatSetter(QProgressBar *bar);

public slots:
    void setFormat(QString format);

private:
    QProgressBar *b;
};

#endif // MAINWINDOW_H
