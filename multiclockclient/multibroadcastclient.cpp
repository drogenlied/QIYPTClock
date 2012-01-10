#include "multibroadcastclient.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QString>
#include <QPair>

MultiBroadcastClient::MultiBroadcastClient(QObject *parent) :
    QObject(parent)
{
    mp.clear();
}

MultiBroadcastClient::~MultiBroadcastClient(){
    for(QMap<unsigned int,SocketHelper*>::Iterator i = mp.begin(); i != mp.end() ; i++){
        delete i.value();
    }
    qDebug("MultiBroadcastClient died");
}

void MultiBroadcastClient::loadFromFile(QString path){
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    mp.clear();

    QTextStream in(&file);
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList sl = line.split(QChar('\t'));
        if(sl.size() == 3){
             int port = sl.value(0).toInt();
             int signature = sl.value(1).toInt();
             QString title = sl.at(2);
             SignalHelper *sh = new SignalHelper(title);

             if (mp.contains(port)){
                 mp[port]->setSignalHelper(signature, sh);
             } else {
                 mp.insert(port, new SocketHelper(port));
                 mp[port]->setSignalHelper(signature, sh);
             }
             //qDebug("blub! %d %d %d\n",sl.value(0).toInt(), sl.value(1).toInt(), mp.size() );
             emit newClock(sh);
        }
    }
    file.close();
    //qDebug("blub");
}
