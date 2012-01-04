#ifndef SIGNALHELPER_H
#define SIGNALHELPER_H

#include <QObject>
#include <QString>

class SignalHelper : public QObject
{
    Q_OBJECT
public:
    explicit SignalHelper( QString title = QString("No Title set"), QObject *parent = 0);
    void fireSignal(quint32 time, quint32 allowedTime, QString stageName);
    QString getTitle();
    QString toString();

signals:
    void allowedTimeChanged(int);
    void timeUpdate(int);
    void timeUpdate(QString);
    void stageNameChanged(QString);

public slots:

private:
    QString title;
    QString stageName;
    quint32 time;
    quint32 allowedTime;

};

#endif // SIGNALHELPER_H
