#ifndef SOCKETHELPER_H
#define SOCKETHELPER_H

#include <QObject>
#include <QtNetwork/QUdpSocket>
#include <QMap>
#include "signalhelper.h"

class SocketHelper : public QObject
{
    Q_OBJECT
public:
    explicit SocketHelper(unsigned int port = 54545, QObject *parent = 0);
    ~SocketHelper();
    void setSignalHelper(unsigned int signature, SignalHelper* s);

signals:

private slots:
    void processDatagrams();

private:
    QUdpSocket *udpSocket;
    unsigned int port;
    QMap<unsigned int, SignalHelper*> sigmap;
};

#endif // SOCKETHELPER_H
