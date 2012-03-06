/****************************************************************************
**
** Copyright (C) 2011 Jan M. Binder
** Contact: jan.binder@sfz-bw.de
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

#ifndef BROADCASTCLIENT_H
#define BROADCASTCLIENT_H

#include <QObject>
#include <QtNetwork/QUdpSocket>

class BroadcastClient : public QObject
{
    Q_OBJECT
public:
    explicit BroadcastClient(QObject *parent = 0, unsigned int port = 54545, unsigned int signature = 123456);
    ~BroadcastClient();
    QString toString();

signals:
    void allowedTimeChanged(int);
    void timeUpdate(int);
    void timeUpdate(QString);
    void stageNameChanged(QString);
    void roomClockChanged(bool);

public slots:
    void setListeningPort(unsigned int);
    void setSignature(unsigned int);

private slots:
    void processDatagrams();

private:
    QUdpSocket *udpSocket;
    unsigned int port;
    QString stagename;
    quint32 time;
    quint32 allowedtime;
    quint32 roomclock;
    quint32 signature;
};

#endif // BROADCASTCLIENT_H
