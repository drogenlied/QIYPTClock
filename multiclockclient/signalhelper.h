#ifndef SIGNALHELPER_H
#define SIGNALHELPER_H

#include <QObject>

template <class T> class SignalHelper : public QObject
{
    Q_OBJECT
public:
    explicit SignalHelper(QObject *parent = 0);
    void fireSignal(T);g

signals:
    void sig(T);

public slots:

};

#endif // SIGNALHELPER_H
