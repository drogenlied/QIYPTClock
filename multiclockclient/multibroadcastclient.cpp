#include "multibroadcastclient.h"
#include <QFile>
#include <QTextStream>
#include <QStringList>
#include <QString>
#include <QPair>

MultiBroadcastClient::MultiBroadcastClient(QObject *parent) :
    QObject(parent)
{
}

void MultiBroadcastClient::loadFromFile(QString path){
    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    lst.clear();

    QTextStream in(&file);
    while (!in.atEnd()) {
        QPair<QPair<unsigned int, unsigned int>, SignalHelper* > elem;
        QString line = in.readLine();
        QStringList sl = line.split(QChar('\t'));
        if(sl.size() == 3){
             elem.first.first = sl.value(0).toInt();
             elem.first.second = sl.value(1).toInt();
             QString s = sl.at(2);
             elem.second = new SignalHelper(this, s);
             lst.append(elem);
             //qDebug("blub! %d %d %d\n",sl.value(0).toInt(), sl.value(1).toInt(), s.size() );
        }
    }
    file.close();

    for(int i = 0; i < lst.size(); ++i){
        emit newClock(lst.at(i).second);
    }
    //qDebug("blub! %d\n",lst.size());
}
