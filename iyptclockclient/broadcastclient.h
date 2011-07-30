#ifndef BROADCASTCLIENT_H
#define BROADCASTCLIENT_H

#include <QObject>
#include <QtNetwork/QUdpSocket>

class BroadcastClient : public QObject
{
    Q_OBJECT
public:
    explicit BroadcastClient(QObject *parent = 0, unsigned int port = 54545);
    ~BroadcastClient();
    QString toString();

signals:
    void allowedTimeChanged(int);
    void timeUpdate(int);
    void timeUpdate(QString);
    void stageNameChanged(QString);

public slots:
    void setListeningPort(unsigned int);

private slots:
    void processDatagrams();

private:
    QUdpSocket *udpSocket;
    unsigned int port;
    QString stagename;
    quint32 time;
    quint32 allowedtime;
    quint32 signature;
};

#endif // BROADCASTCLIENT_H
