#include "broadcastserver.h"

BroadcastServer::BroadcastServer(QObject *parent) :
    QObject(parent)
{
    udpSocket = new QUdpSocket(this);
}

BroadcastServer::~BroadcastServer(){
    delete udpSocket;
}

void BroadcastServer::setStageName(QString name){

}

void BroadcastServer::setAllowedTime(int t){

}

void BroadcastServer::updateTime(int t){

}

void BroadcastServer::setBroadcastPort(int p){

}
