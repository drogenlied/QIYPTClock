#ifndef BROADCASTSERVER_H
#define BROADCASTSERVER_H

#include <QObject>
#include <QtNetwork/QUdpSocket>

class BroadcastServer : public QObject
{
    Q_OBJECT
public:
    explicit BroadcastServer(QObject *parent = 0, unsigned int p = 54545);
    ~BroadcastServer();

signals:
    void socketStatus();
    void updated();

public slots:
    void setStageName(QString);
    void setAllowedTime(int);
    void updateTime(int);
    void setBroadcastPort(unsigned int);

private slots:
    void broadcast();

private:
    QUdpSocket *udpSocket;
    QString stagename;
    int allowedtime, time;
    unsigned int port;
};

#endif // BROADCASTSERVER_H
