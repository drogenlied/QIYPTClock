/****************************************************************************
**
** Copyright (C) 2011-2012 Jan M. Binder, Simeon Voelkel
** Contact: jan.binder@sfz-bw.de, simeon.voelkel@sfz-bw.de
**
** $QT_BEGIN_LICENSE:GPL$
** GNU General Public License Usage
** This file may be used under the terms of the GNU
** General Public License version 3.0 as published by the Free Software
** Foundation and appearing in the file LICENSE.GPL included in the
** packaging of this file.  Please review the following information to
** ensure the GNU General Public License version 3.0 requirements will be
** met: http://www.gnu.org/copyleft/gpl.html.
** $QT_END_LICENSE$
**
****************************************************************************/

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
    int getElapsedTime();
    bool isRunning();

signals:
    void allowedTimeChanged(int);
    void overtimed(int);
    void timeUpdate(int);
    void timeUpdate(QString);
    void started(int);
    void paused(int);
    void stopped(int);
    void restarted(int);

public slots:
    void startorpause();
    void stop();
    void reset();
    void setAllowedTime(int ms);
    void setOverTime(int ms);
    void setElapsedTime(int ms);
    void setRemainingTime(int ms);
    void pulse();

private:
    QTime *t;
    QTimer *renew;
    int maxtime;
    int overtime;
    int savedtime;
    bool running;
};

#endif // THEMECLOCK_H
