#ifndef MULTIBROADCASTCLIENT_H
#define MULTIBROADCASTCLIENT_H

#include <QObject>
#include <QVector>
#include <QPair>

class MultiBroadcastClient : public QObject
{
    Q_OBJECT
public:
    explicit MultiBroadcastClient(QObject *parent = 0);

signals:

public slots:
    void loadFromFile(QString path);

private:
    QVector<QPair<unsigned int, unsigned int> > lst;
};

#endif // MULTIBROADCASTCLIENT_H
