/****************************************************************************
**
** Copyright (C) 2011-2012 Jan M. Binder, Simeon Voelkel
** Contact: jan.binder@sfz-bw.de, simeon.voelkel@sfz-bw.de
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
#include "broadcastclient.h"
#include <QTimer>

MainWindow::MainWindow(unsigned int port, unsigned int sig, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   
    ui->setupUi(this);
//    connect(ui->portButton, SIGNAL(clicked()), this, SLOT(triggerPort()));
//    connect(ui->idButton, SIGNAL(clicked()), this, SLOT(triggerId()));

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), ui->graphicsView, SLOT(act()));
    timer->start(30);
//    qDebug("p, s: %d, %d\n",port,sig);

    BroadcastClient *bc = new BroadcastClient(this, port, sig);

    connect(bc, SIGNAL(timeUpdate(int)), ui->graphicsView, SLOT(setTime(int)));
    connect(bc, SIGNAL(timeUpdate(int)), this, SLOT(setLcdWidthForTime(int)));
    connect(bc, SIGNAL(roomClockChanged(bool)), ui->graphicsView, SLOT(setRoomclock(bool)));
    connect(bc, SIGNAL(allowedTimeChanged(int)), ui->graphicsView, SLOT(setAllowedTime(int)));
    connect(bc, SIGNAL(timeUpdate(QString)), ui->lcdNumber, SLOT(display(QString)));
    connect(bc, SIGNAL(stageNameChanged(QString)), ui->stageLabel, SLOT(setText(QString)));
    connect(this, SIGNAL(newPort(uint)), bc, SLOT(setListeningPort(uint)));
    connect(this, SIGNAL(newID(uint)), bc, SLOT(setSignature(uint)));

    ui->graphicsView->setRoomclock(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setLcdWidthForTime(int time){
    if (time < 0) return;
    else if (time < 600000) ui->lcdNumber->setDigitCount(4);
    else if (time < 3600000) ui->lcdNumber->setDigitCount(5);
    else if (time < 36000000) ui->lcdNumber->setDigitCount(7);
    else ui->lcdNumber->setDigitCount(8);
}

//void MainWindow::triggerId(){
//    emit newID((unsigned int)(ui->idBox->value()));
//}

//void MainWindow::triggerPort(){
//    emit newPort((unsigned int)(ui->portBox->value()));
//}
