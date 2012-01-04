#ifndef MULTIBROADCASTCLIENT_H
#define MULTIBROADCASTCLIENT_H

#include <QObject>
#include <QVector>
#include <QMap>
#include "signalhelper.h"
#include "sockethelper.h"

class MultiBroadcastClient : public QObject
{
    Q_OBJECT
public:
    explicit MultiBroadcastClient(QObject *parent = 0);

signals:
    void newClock(SignalHelper*);

public slots:
    void loadFromFile(QString path);

private:
    QMap<unsigned int, SocketHelper*> mp;
};

#endif // MULTIBROADCASTCLIENT_H
