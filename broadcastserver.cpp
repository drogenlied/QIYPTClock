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

#include "broadcastserver.h"
#include <QDataStream>
#include <QtNetwork>

BroadcastServer::BroadcastServer(QObject *parent, QHostAddress addr, unsigned int p, unsigned int sig) :
    QObject(parent)
{
    udpSocket = new QUdpSocket(this);
    if(p > 0){
        port = p%65536;
    }else{
        port = 54545;
    }
    signature = sig;
    broadcastAddress = addr;
    connect(this, SIGNAL(updated()), this, SLOT(broadcast()));
}

BroadcastServer::~BroadcastServer(){
    delete udpSocket;
}

void BroadcastServer::setStageName(QString name){
    stagename = name;
    emit updated();
}

void BroadcastServer::setAllowedTime(int t){
    if (t>0)
        allowedtime = t;
    emit updated();
}

void BroadcastServer::setRoomclock(bool roomclock){
    this->roomclock = roomclock;
    emit updated();
}

void BroadcastServer::updateTime(int t){
    time = t;
    emit updated();
}

void BroadcastServer::setBroadcastAddress(QHostAddress addr){
    broadcastAddress = addr;
}

void BroadcastServer::setBroadcastPort(unsigned int p){
    if (p>0)
        port = p%65536;
    emit updated();
}

void BroadcastServer::setSignature(unsigned int sig){
    signature = sig;
}

void BroadcastServer::broadcast(){
    QByteArray datagram;
    QDataStream dgstream(&datagram, QIODevice::ReadWrite);
    dgstream << (quint32)signature;
    dgstream << (quint32)allowedtime;
    dgstream << (quint32)time;
    dgstream << (quint32)(roomclock? 1 : 0);
    dgstream << stagename;
    //qDebug("dgram: %d", datagram.size());
    udpSocket->writeDatagram(datagram.data(), datagram.size(), broadcastAddress, port);
}
