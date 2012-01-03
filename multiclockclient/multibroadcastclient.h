#ifndef MULTIBROADCASTCLIENT_H
#define MULTIBROADCASTCLIENT_H

#include <QObject>

class MultiBroadcastClient : public QObject
{
    Q_OBJECT
public:
    explicit MultiBroadcastClient(QObject *parent = 0);

signals:

public slots:

};

#endif // MULTIBROADCASTCLIENT_H
