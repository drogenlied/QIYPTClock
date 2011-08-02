#include "broadcastclient.h"
#include <QDataStream>
#include <QtNetwork>

BroadcastClient::BroadcastClient(QObject *parent, unsigned int p) :
    QObject(parent)
{
    if(p > 0){
        port = p%65536;
    }else{
        port = 54545;
    }

    time = 0;
    allowedtime = 1;
    stagename = "";

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(port, QUdpSocket::ShareAddress);

    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processDatagrams()));
}

BroadcastClient::~BroadcastClient(){
    delete udpSocket;
}

void BroadcastClient::setListeningPort(unsigned int p){
    if(p > 0){
        port = p%65536;
    }else{
        port = 54545;
    }
    udpSocket->bind(port, QUdpSocket::ShareAddress);
}

void BroadcastClient::processDatagrams(){
    quint32 nsignature, nallowedtime, ntime;
    QString nstagename;

    while (udpSocket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(udpSocket->pendingDatagramSize());
        udpSocket->readDatagram(datagram.data(), datagram.size());
        QDataStream dgstream(&datagram, QIODevice::ReadOnly);
        dgstream >> nsignature;
        dgstream >> nallowedtime;
        dgstream >> ntime;
        dgstream >> nstagename;
    }
    if (time != ntime){
        time = ntime;
        emit timeUpdate(time);
        emit timeUpdate(this->toString());
    }
    if (allowedtime != nallowedtime){
        allowedtime = nallowedtime;
        emit allowedTimeChanged(allowedtime);
    }
    if (nstagename != stagename){
        stagename = nstagename;
        emit stageNameChanged(stagename);
    }
}

QString BroadcastClient::toString(){
    QTime tmp = QTime(0,0,0,0);
    tmp = tmp.addMSecs(time);
    QString s = tmp.toString("hh:mm:ss.zzz");
    s.chop(2);
    return s;
}
