#include "broadcastserver.h"

BroadcastServer::BroadcastServer(QObject *parent) :
    QObject(parent)
{
    udpSocket = new QUdpSocket(this);
}

BroadcastServer::~BroadcastServer(){
    delete udpSocket;
}
