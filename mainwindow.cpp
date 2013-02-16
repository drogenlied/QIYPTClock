/****************************************************************************
**
** Copyright (C) 2011-2012 Jan M. Binder, Felix Engelmann, Simeon Voelkel
** Contact: jan.binder@sfz-bw.de, felix.engelmann@sfz-bw.de,
**          simeon.voelkel@sfz-bw.de
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
#include <QFile>
#include <tclap/CmdLine.h>
#include <string>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    unsigned int sig = 123456;
    unsigned int port = 54545;
    std::string addressString = "255.255.255.255";
    bool noconfig = false;

    try {
        TCLAP::CmdLine cmd("iyptclock", ' ', "0.9");
        TCLAP::ValueArg<unsigned int> portArg("p", "port","Port to listen on", false, 54545, "unsigned integer");
        TCLAP::ValueArg<unsigned int> sigArg("s", "signature","Signature to use", false, 123456 , "unsigned integer");
        TCLAP::ValueArg<std::string> bcastArg("b", "broadcast","Broadcast address to send packets to", false, "255.255.255.255", "ip address");
        TCLAP::SwitchArg noconfigArg("n", "noconfig", "disable configuration", false);

        cmd.add( portArg );
        cmd.add( sigArg );
        cmd.add( bcastArg );
        cmd.add( noconfigArg );
        cmd.parse( QApplication::argc(), QApplication::argv() );

        port = portArg.getValue();
        sig = sigArg.getValue();
        addressString = bcastArg.getValue();
        noconfig = noconfigArg.getValue();

    } catch (TCLAP::ArgException &e) {
        std::cerr << "error: " << e.error() << " for arg " << e.argId() << std::endl;
    }

    ui->setupUi(this);

    connect(ui->idButton, SIGNAL(clicked()), this, SLOT(triggerId()));
    connect(ui->portButton, SIGNAL(clicked()), this, SLOT(triggerPort()));
    connect(ui->startstop, SIGNAL(clicked()), this, SLOT(toggleStartPause()));
    connect(ui->delButton, SIGNAL(clicked()), this, SLOT(triggerDel()));
    connect(ui->saveButton, SIGNAL(clicked()), this, SLOT(saveStages()));

    ad = new AboutDialog();

    connect(ui->actionAbout_IYPTClock, SIGNAL(triggered()), ad, SLOT(exec()));

    timer = new QTimer();
    connect(timer, SIGNAL(timeout()), ui->graphicsView, SLOT(act()));
    timer->start(30);

    thc = new ThemeClock();

    connect(thc, SIGNAL(timeUpdate(int)), ui->graphicsView, SLOT(setTime(int)));
    connect(thc, SIGNAL(allowedTimeChanged(int)), ui->graphicsView, SLOT(setAllowedTime(int)));
    connect(thc, SIGNAL(started(int)), ui->graphicsView, SLOT(setTime(int)));
    connect(thc, SIGNAL(paused(int)), ui->graphicsView, SLOT(setTime(int)));
    connect(thc, SIGNAL(restarted(int)), ui->graphicsView, SLOT(setTime(int)));
    connect(thc, SIGNAL(stopped(int)), ui->graphicsView, SLOT(setTime(int)));
    connect(ui->startstop, SIGNAL(clicked()), thc, SLOT(startorpause()));
    connect(ui->resetButton, SIGNAL(clicked()), thc, SLOT(reset()));
    connect(ui->setTimeButton, SIGNAL(clicked()), this, SLOT(setTime()));
    ui->setTimeComboBox->addItem(tr("last saved time"), QVariant(TIME_SAVED));
    ui->setTimeComboBox->addItem(tr("elapsed time"), QVariant(TIME_ELAPSED));
    ui->setTimeComboBox->addItem(tr("remaining time"), QVariant(TIME_LEFT));

    connect(thc, SIGNAL(timeUpdate(QString)), ui->lcdNumber, SLOT(display(QString)));

    lc = new ListController();

    connect(ui->ffwd, SIGNAL(clicked()), lc, SLOT(forward()));
    connect(ui->bwd, SIGNAL(clicked()), lc, SLOT(backward()));
    connect(ui->addButton, SIGNAL(clicked()), lc, SLOT(add()));
    connect(thc, SIGNAL(started(int)), lc, SLOT(checkAutoStart()));
    connect(this, SIGNAL(itemShouldBeDeleted(QModelIndex)), lc, SLOT(del(QModelIndex)));
    connect(lc, SIGNAL(allowedTimeChanged(int)), thc, SLOT(setAllowedTime(int)));
    connect(lc, SIGNAL(roomClockChanged(bool)), ui->graphicsView, SLOT(setRoomclock(bool)));
    connect(lc, SIGNAL(resetTime()), thc, SLOT(reset()));
    connect(lc, SIGNAL(endOfStage()), thc, SLOT(stop()));
    connect(lc, SIGNAL(stageNameChanged(QString)), ui->stageLabel, SLOT(setText(QString)));
    connect(lc, SIGNAL(modelChanged(QAbstractTableModel*)), this, SLOT(propagateModel(QAbstractTableModel*)));

    ui->portBox->setValue(port);
    ui->idBox->setValue(sig);

    bs = new BroadcastServer(this, QHostAddress(addressString.c_str()), port, sig);

    connect(thc, SIGNAL(timeUpdate(int)), bs, SLOT(updateTime(int)));
    connect(thc, SIGNAL(restarted(int)), bs, SLOT(updateTime(int)));
    connect(thc, SIGNAL(stopped(int)), bs, SLOT(updateTime(int)));
    connect(thc, SIGNAL(allowedTimeChanged(int)), bs, SLOT(setAllowedTime(int)));
    connect(lc, SIGNAL(roomClockChanged(bool)), bs, SLOT(setRoomclock(bool)));
    connect(lc, SIGNAL(stageNameChanged(QString)), bs, SLOT(setStageName(QString)));
    connect(this, SIGNAL(newPort(uint)), bs, SLOT(setBroadcastPort(uint)));
    connect(this, SIGNAL(newID(uint)), bs, SLOT(setSignature(uint)));

    connect(lc, SIGNAL(overTimeChanged(int)), thc, SLOT(setOverTime(int)));
    connect(thc, SIGNAL(overtimed(int)), lc, SLOT(handleOvertime(int)));
    connect(lc, SIGNAL(elapsedTimeChanged(int)), thc, SLOT(setElapsedTime(int)));
    connect(lc, SIGNAL(elapsedTimeChanged(int)), ui->graphicsView, SLOT(setTime(int)));
    connect(lc, SIGNAL(elapsedTimeChanged(int)), bs, SLOT(updateTime(int)));
    connect(lc, SIGNAL(getElapsedOverTime()), thc, SLOT(getElapsedOverTime()));
    connect(thc, SIGNAL(elapsedOverTime(int)), lc, SLOT(setElapsedOverTime(int)));

    if (noconfig)
      {
        ui->tabWidget->setTabEnabled(1,false);
      }

    if (QFile("stages.txt").exists()){
        lc->loadListFromFile("stages.txt");
    } else if (QFile("/usr/share/iyptclock/stages.txt").exists()){
        lc->loadListFromFile("/usr/share/iyptclock/stages.txt");
    } else {
        lc->loadListFromFile("");
    }
    thc->stop();

    timer2 = new QTimer();
    connect(timer2, SIGNAL(timeout()), this, SLOT(toggleStartPause()));
    connect(timer2, SIGNAL(timeout()), this, SLOT(toggleTimeSpinBox()));
    timer2->start(100);

    savefile = QString("/var/run/iyptclock/autosave_");
    savefile += QString::number(sig);

    as = new AutoSave(this,savefile,this);
    as->load();

    timer3 = new QTimer();
    connect(timer3, SIGNAL(timeout()),as,SLOT(save()));
    timer3->start(1000);
}

MainWindow::~MainWindow()
{
    delete timer;
    delete bs;
    delete lc;
    delete thc;
    delete ad;
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
    emit newID((unsigned int)(ui->idBox->value()));
}

void MainWindow::triggerPort(){
    emit newPort((unsigned int)(ui->portBox->value()));
}

void MainWindow::triggerDel(){
    emit itemShouldBeDeleted(ui->tableView->currentIndex());
}

void MainWindow::toggleStartPause(){
    if(thc->isRunning()){
        ui->startstop->setText("Pause");
    }else{
        ui->startstop->setText("Start");
    }
}

void MainWindow::toggleTimeSpinBox(){
    if (ui->setTimeComboBox->itemData(ui->setTimeComboBox->currentIndex()).toInt() == TIME_SAVED){
      ui->setTimeSpinBox->setEnabled(false);
      ui->setTimeSpinBox->setValue(as->getLastSavedTime()/1000);
    }else{
      ui->setTimeSpinBox->setEnabled(true);
    }
}

void MainWindow::saveStages(){
    lc->saveListToFile("stages.txt");
}

void MainWindow::setTime(){
    switch (ui->setTimeComboBox->itemData(ui->setTimeComboBox->currentIndex()).toInt()) {
    case TIME_SAVED:
            thc->setElapsedTime(as->getLastSavedTime());
            break;
    case TIME_ELAPSED:
            thc->setElapsedTime(ui->setTimeSpinBox->value()*1000);
            break;
    case TIME_LEFT:
            thc->setRemainingTime(ui->setTimeSpinBox->value()*1000);
            break;
    default:
            break;
    }
}

void MainWindow::propagateModel(QAbstractTableModel* mdl){
    ui->stagelist->setModel(mdl);
    ui->tableView->setModel(mdl);
}

