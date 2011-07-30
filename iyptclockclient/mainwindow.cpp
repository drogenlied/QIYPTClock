#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "broadcastclient.h"
#include <QtCore/QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), ui->graphicsView, SLOT(act()));
    timer->start(30);

    BroadcastClient *bc = new BroadcastClient();

    connect(bc, SIGNAL(timeUpdate(int)), ui->graphicsView, SLOT(setTime(int)));
    connect(bc, SIGNAL(allowedTimeChanged(int)), ui->graphicsView, SLOT(setAllowedTime(int)));
    connect(bc, SIGNAL(timeUpdate(QString)), ui->lcdNumber, SLOT(display(QString)));
    connect(bc, SIGNAL(stageNameChanged(QString)), ui->statusBar, SLOT(setWindowTitle(QString)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
