#ifndef THEMECLOCK_H
#define THEMECLOCK_H

#include <QObject>
#include <QtCore/QTime>
#include <QtCore/QTimer>

class ThemeClock : public QObject
{
    Q_OBJECT
public:
    explicit ThemeClock(QObject *parent = 0);
    ~ThemeClock();
    QString toString();

signals:
    void allowedTimeChanged(int);
    void timeUpdate(int);
    void timeUpdate(QString);
    void started(int);
    void paused(int);
    void restarted(int);

public slots:
    void startorpause();
    void reset();
    void setAllowedTime(int ms);
    void pulse();

private:
    QTime *t;
    QTimer *renew;
    int maxtime;
    int savedtime;
    bool running;
};

#endif // THEMECLOCK_H
