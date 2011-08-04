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

#include "themeclock.h"

ThemeClock::ThemeClock(QObject *parent) :
    QObject(parent) {
    t = new QTime();
    renew = new QTimer();
    connect(renew, SIGNAL(timeout()), this, SLOT(pulse()));
    running = false;
    savedtime = 0;
    renew->start(10);
}

ThemeClock::~ThemeClock(){
    delete t;
    delete renew;
}

void ThemeClock::startorpause(){
    if (running){
        savedtime = t->elapsed();
        running = false;
        emit paused(savedtime);
    } else {
        t->start();
        *t = t->addMSecs(-savedtime);
        running = true;
        emit started(t->elapsed());
    }
    emit allowedTimeChanged(maxtime);
}

void ThemeClock::stop(){
    savedtime = 0;
    running = false;
    emit stopped(0);
}

void ThemeClock::reset(){
    savedtime = 0;
    t->restart();
    emit restarted(0);
}

void ThemeClock::setAllowedTime(int ms){
    if (ms > 0){
    maxtime = ms;
    emit allowedTimeChanged(maxtime);
    }
}

void ThemeClock::pulse(){
    if(running) {
        emit timeUpdate(t->elapsed());
        emit timeUpdate(this->toString());
    }
}

QString ThemeClock::toString(){
    QTime tmp = QTime(0,0,0,0);
    tmp = tmp.addMSecs(t->elapsed());
    QString s = tmp.toString("hh:mm:ss.zzz");
    s.chop(2);
    return s;
}
