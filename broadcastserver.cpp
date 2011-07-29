#include "broadcastserver.h"
#include <QDataStream>
#include <QtNetwork>
#include <QDataStream>

BroadcastServer::BroadcastServer(QObject *parent, unsigned int p) :
    QObject(parent)
{
    udpSocket = new QUdpSocket(this);
    if (p < INT_MAX) {
        port = p;
    }else{
        port = p/2;
    }
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

void BroadcastServer::updateTime(int t){
    time = t;
    emit updated();
}

void BroadcastServer::setBroadcastPort(unsigned int p){
    if (p>0)
        port = p;
    emit updated();
}

void BroadcastServer::broadcast(){
    QByteArray datagram;
    QDataStream dgstream(&datagram, QIODevice::ReadWrite);
    dgstream << (quint32)0xABCDEF;
    dgstream << (quint32)allowedtime;
    dgstream << (quint32)time;
    dgstream << stagename;
    qDebug("dgram: %d", datagram.size());
    udpSocket->writeDatagram(datagram.data(), datagram.size(), QHostAddress::Broadcast, port);
}
