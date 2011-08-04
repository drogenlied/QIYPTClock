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
