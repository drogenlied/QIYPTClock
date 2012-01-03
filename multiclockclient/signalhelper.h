#ifndef SIGNALHELPER_H
#define SIGNALHELPER_H

#include <QObject>

class SignalHelper : public QObject
{
    Q_OBJECT
public:
    explicit SignalHelper(QObject *parent = 0);
    void fireSignal(int s);

signals:
    void allowedTimeChanged(int);
    void timeUpdate(int);
    void timeUpdate(QString);
    void stageNameChanged(QString);

public slots:

};

#endif // SIGNALHELPER_H
