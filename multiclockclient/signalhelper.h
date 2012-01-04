#ifndef SIGNALHELPER_H
#define SIGNALHELPER_H

#include <QObject>

class SignalHelper : public QObject
{
    Q_OBJECT
public:
    explicit SignalHelper(QObject *parent = 0);
    SignalHelper(QObject *parent = 0, QString title = QString("No Title set"));
    void fireSignal(int s);
    QString getTitle();

signals:
    void allowedTimeChanged(int);
    void timeUpdate(int);
    void timeUpdate(QString);
    void stageNameChanged(QString);

public slots:

private:
    QString title;

};

#endif // SIGNALHELPER_H
