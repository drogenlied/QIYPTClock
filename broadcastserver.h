#ifndef BROADCASTSERVER_H
#define BROADCASTSERVER_H

#include <QObject>
#include <QtNetwork/QUdpSocket>

class BroadcastServer : public QObject
{
    Q_OBJECT
public:
    explicit BroadcastServer(QObject *parent = 0);
    ~BroadcastServer();

signals:
    void connectionStatus();

public slots:
    void setStageName(QString);
    void setAllowdTime(int);
    void updateTime(int);
    void setBroadcastPort(int);

private:
    QUdpSocket *udpSocket;
    QString stagename;
    int allowedtime, time, port;
};

#endif // BROADCASTSERVER_H
