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
#include "broadcastclient.h"
#include <QtCore/QTimer>
#include <tclap/CmdLine.h>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{   
    unsigned int sig, port;
    try {
        TCLAP::CmdLine cmd("iyptclockclient", ' ', "0.9");
        TCLAP::ValueArg<unsigned int> portArg("p","port","Port to listen on",false, 54545,"unsigned integer");
        TCLAP::ValueArg<unsigned int> sigArg("s","signature","Signature to use",false, 123456 ,"unsigned integer");

        cmd.add( portArg );
        cmd.add( sigArg );
        cmd.parse( QApplication::argc(), QApplication::argv() );

        port = portArg.getValue();
        sig = sigArg.getValue();

    } catch (TCLAP::ArgException &e) {
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
    }

    ui->setupUi(this);
//    connect(ui->portButton, SIGNAL(clicked()), this, SLOT(triggerPort()));
//    connect(ui->idButton, SIGNAL(clicked()), this, SLOT(triggerId()));

    QTimer *timer = new QTimer();
    connect(timer, SIGNAL(timeout()), ui->graphicsView, SLOT(act()));
    timer->start(30);
    qDebug("p, s: %d, %d\n",port,sig);

    BroadcastClient *bc = new BroadcastClient(this, port, sig);

    connect(bc, SIGNAL(timeUpdate(int)), ui->graphicsView, SLOT(setTime(int)));
    connect(bc, SIGNAL(allowedTimeChanged(int)), ui->graphicsView, SLOT(setAllowedTime(int)));
    connect(bc, SIGNAL(timeUpdate(QString)), ui->lcdNumber, SLOT(display(QString)));
    connect(bc, SIGNAL(stageNameChanged(QString)), ui->stageLabel, SLOT(setText(QString)));
    connect(this, SIGNAL(newPort(uint)), bc, SLOT(setListeningPort(uint)));
    connect(this, SIGNAL(newID(uint)), bc, SLOT(setSignature(uint)));

}

MainWindow::~MainWindow()
{
    delete ui;
}

//void MainWindow::triggerId(){
//    emit newID((unsigned int)(ui->idBox->value()));
//}

//void MainWindow::triggerPort(){
//    emit newPort((unsigned int)(ui->portBox->value()));
//}
