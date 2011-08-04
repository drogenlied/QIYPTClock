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

#ifndef BROADCASTSERVER_H
#define BROADCASTSERVER_H

#include <QObject>
#include <QtNetwork/QUdpSocket>

class BroadcastServer : public QObject
{
    Q_OBJECT
public:
    explicit BroadcastServer(QObject *parent = 0, unsigned int p = 54545);
    ~BroadcastServer();

signals:
    void socketStatus();
    void updated();

public slots:
    void setStageName(QString);
    void setAllowedTime(int);
    void updateTime(int);
    void setBroadcastPort(unsigned int);
    void setSignature(unsigned int);

private slots:
    void broadcast();

private:
    QUdpSocket *udpSocket;
    QString stagename;
    int allowedtime, time;
    unsigned int port, signature;
};

#endif // BROADCASTSERVER_H
