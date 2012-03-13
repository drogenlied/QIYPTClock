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

#include "broadcastclient.h"
#include <QDataStream>
#include <QtNetwork>

BroadcastClient::BroadcastClient(QObject *parent, unsigned int p, unsigned int sig) :
    QObject(parent)
{
    if(p > 0){
        port = p%65536;
    }else{
        port = 54545;
    }
    signature = sig;

    time = 0;
    allowedtime = 1;
    roomclock = 2;
    stagename = "";

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(port, QUdpSocket::ShareAddress);

    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processDatagrams()));
}

BroadcastClient::~BroadcastClient(){
    delete udpSocket;
}

void BroadcastClient::setListeningPort(unsigned int p){
    udpSocket->close();
    if(p > 0){
        port = p%65536;
    }else{
        port = 54545;
    }
    udpSocket->bind(port, QUdpSocket::ShareAddress);
}

void BroadcastClient::setSignature(unsigned int sig){
    signature = sig;
}

void BroadcastClient::processDatagrams(){
    quint32 nsignature, nallowedtime, nroomclock, ntime;
    QString nstagename;

    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
        QDataStream dgstream(&datagram, QIODevice::ReadOnly);
        dgstream >> nsignature;
        dgstream >> nallowedtime;
        dgstream >> ntime;
        dgstream >> nroomclock;
        dgstream >> nstagename;
    }
    if (signature != nsignature)
        return;

    if (time != ntime){
        time = ntime;
        emit timeUpdate(time);
        emit timeUpdate(this->toString());
    }
    if (allowedtime != nallowedtime){
        allowedtime = nallowedtime;
        emit allowedTimeChanged(allowedtime);
    }
    if (roomclock != nroomclock){
        roomclock = nroomclock;
        emit roomClockChanged(roomclock > 0);
    }
    if (nstagename != stagename){
        stagename = nstagename;
        emit stageNameChanged(stagename);
    }
}

QString BroadcastClient::toString(){
    QTime tmp = QTime(0,0,0,0);
    tmp = tmp.addMSecs(time);
    QString s = tmp.toString("mm:ss");
    //s.chop(2);
    return s;
}
