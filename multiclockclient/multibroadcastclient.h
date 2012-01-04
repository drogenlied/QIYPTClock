#ifndef MULTIBROADCASTCLIENT_H
#define MULTIBROADCASTCLIENT_H

#include <QObject>
#include <QVector>
#include <QPair>
#include "signalhelper.h"

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
    QVector<QPair<QPair<unsigned int, unsigned int>, SignalHelper*> > lst;
};

#endif // MULTIBROADCASTCLIENT_H
