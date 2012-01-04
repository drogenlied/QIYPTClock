#include "sockethelper.h"
#include <QDataStream>
#include <QtNetwork>

SocketHelper::SocketHelper(unsigned int p, QObject *parent) :
    QObject(parent)
{
    if(p > 0){
        port = p%65536;
    }else{
        port = 54545;
    }

    udpSocket = new QUdpSocket(this);
    udpSocket->bind(port, QUdpSocket::ShareAddress);

    connect(udpSocket, SIGNAL(readyRead()), this, SLOT(processDatagrams()));
}

void SocketHelper::setSignalHelper(unsigned int signature, SignalHelper* s){
    if(sigmap.contains(signature)){
        sigmap[signature] = s;
    } else {
        sigmap.insert(signature, s);
    }
}

void SocketHelper::processDatagrams(){
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

        if (sigmap.contains(nsignature)){
            sigmap[nsignature]->fireSignal(ntime, nallowedtime, nstagename);
        }
    }
}
