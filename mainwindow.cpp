/****************************************************************************
**
** Copyright (C) 2011 Jan M. Binder
** Contact: jan.binder@sfz-bw.de
**
** $QT_BEGIN_LICENSE:GPL$
** GNU General Public License Usage
** This file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
** $QT_END_LICENSE$
**
****************************************************************************/

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "themeclock.h"
#include "listcontroller.h"
#include "broadcastserver.h"
#include <QtCore/QTimer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->idButton, SIGNAL(clicked()), this, SLOT(triggerId()));
    connect(ui->portButton, SIGNAL(clicked()), this, SLOT(triggerPort()));

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), ui->graphicsView, SLOT(act()));
    timer->start(30);

    ThemeClock *thc = new ThemeClock();

    connect(thc, SIGNAL(timeUpdate(int)), ui->graphicsView, SLOT(setTime(int)));
    connect(thc, SIGNAL(allowedTimeChanged(int)), ui->graphicsView, SLOT(setAllowedTime(int)));
    connect(thc, SIGNAL(started(int)), ui->graphicsView, SLOT(setTime(int)));
    connect(thc, SIGNAL(paused(int)), ui->graphicsView, SLOT(setTime(int)));
    connect(thc, SIGNAL(restarted(int)), ui->graphicsView, SLOT(setTime(int)));
    connect(thc, SIGNAL(stopped(int)), ui->graphicsView, SLOT(setTime(int)));

    connect(ui->startstop, SIGNAL(clicked()), thc, SLOT(startorpause()));
    connect(ui->resetButton, SIGNAL(clicked()), thc, SLOT(reset()));
    connect(thc, SIGNAL(timeUpdate(QString)), ui->lcdNumber, SLOT(display(QString)));

    ListController *lc = new ListController();

    connect(ui->ffwd, SIGNAL(clicked()), lc, SLOT(forward()));
    connect(ui->bwd, SIGNAL(clicked()), lc, SLOT(backward()));
    connect(lc, SIGNAL(allowedTimeChanged(int)), thc, SLOT(setAllowedTime(int)));
    connect(lc, SIGNAL(resetTime()), thc, SLOT(reset()));

    BroadcastServer *bs = new BroadcastServer();

    connect(thc, SIGNAL(timeUpdate(int)), bs, SLOT(updateTime(int)));
    connect(thc, SIGNAL(restarted(int)), bs, SLOT(updateTime(int)));
    connect(thc, SIGNAL(allowedTimeChanged(int)), bs, SLOT(setAllowedTime(int)));
    connect(lc, SIGNAL(stageNameChanged(QString)), bs, SLOT(setStageName(QString)));
    connect(this, SIGNAL(newPort(uint)), bs, SLOT(setBroadcastPort(uint)));
    connect(this, SIGNAL(newID(uint)), bs, SLOT(setSignature(uint)));

    thc->setAllowedTime(20000);

    lc->loadListFromFile("stages.txt");
    ui->tableView->setModel(lc->getModel());
    ui->stagelist->setModel(lc->getModel());

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

void MainWindow::triggerId(){
    emit (unsigned int)(ui->idBox->value());
}

void MainWindow::triggerPort(){
    emit (unsigned int)(ui->portBox->value());
}
