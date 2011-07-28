#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "themeclock.h"
#include "listcontroller.h"
#include <QtCore/QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setRenderHint(QPainter::SmoothPixmapTransform);


    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), ui->graphicsView, SLOT(act()));
    timer->start(100);

    ThemeClock *thc = new ThemeClock();

    connect(thc, SIGNAL(timeUpdate(int)), ui->graphicsView, SLOT(setTime(int)));
    connect(thc, SIGNAL(allowedTimeChanged(int)), ui->graphicsView, SLOT(setAllowedTime(int)));
    connect(thc, SIGNAL(started(int)), ui->graphicsView, SLOT(setTime(int)));
    connect(thc, SIGNAL(paused(int)), ui->graphicsView, SLOT(setTime(int)));
    connect(thc, SIGNAL(restarted(int)), ui->graphicsView, SLOT(setTime(int)));
    connect(thc, SIGNAL(stopped(int)), ui->graphicsView, SLOT(setTime(int)));

    connect(ui->startstop, SIGNAL(clicked()), thc, SLOT(startorpause()));
    connect(thc, SIGNAL(timeUpdate(QString)), ui->lcdNumber, SLOT(display(QString)));

    ListController *lc = new ListController();

    connect(ui->ffwd, SIGNAL(clicked()), lc, SLOT(forward()));
    connect(ui->bwd, SIGNAL(clicked()), lc, SLOT(backward()));
    connect(lc, SIGNAL(newAllowedTime(int)), thc, SLOT(setAllowedTime(int)));
    connect(lc, SIGNAL(resetTime()), thc, SLOT(reset()));

    thc->setAllowedTime(20000);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
