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

#include <QApplication>
#include <QCommandLineParser>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    unsigned int sig = 123456;
    unsigned int port = 54545;
    QString addressString = "255.255.255.255";
    QHostAddress qHa = QHostAddress(addressString);
    bool noconfig = false;

    QApplication a(argc, argv);
    QApplication::setApplicationName("iyptclock");
    QApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Test helper");

    QCommandLineOption portOption(QStringList() << "p" << "port",
                                  QCoreApplication::translate("main", "Port to listen on"),
                                  QCoreApplication::translate("main", "port"));

    QCommandLineOption signatureOption(QStringList() << "s" << "signature",
                                  QCoreApplication::translate("main", "Signature to use"),
                                  QCoreApplication::translate("main", "signature"));

    QCommandLineOption broadcastOption(QStringList() << "b" << "broadcast",
                                  QCoreApplication::translate("main", "Broadcast address to send packets to"),
                                  QCoreApplication::translate("main", "broadcast address"));

    QCommandLineOption noconfigOption(QStringList() << "n" << "noconfig",
                                   QCoreApplication::translate("main", "disable configuration file"));

    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOption(portOption);
    parser.addOption(signatureOption);
    parser.addOption(broadcastOption);
    parser.addOption(noconfigOption);
    parser.process(a);

    if (parser.isSet(broadcastOption)) {
        QString tmpAddressString = parser.value(broadcastOption);
        qHa = QHostAddress(tmpAddressString);
    }
    if (parser.isSet(portOption)) {
        unsigned int tmpPort = parser.value(portOption).toUInt();
        if (tmpPort > 0 && tmpPort < 65536){
            port = tmpPort;
        }
    }
    if (parser.isSet(signatureOption)) {
        unsigned int tmpSig = parser.value(signatureOption).toUInt();
        if (tmpSig > 0) {
            sig = tmpSig;
        }
    }

    noconfig = parser.isSet(noconfigOption);



    MainWindow w(nullptr, qHa, port, sig, noconfig);
    w.show();
    return a.exec();
}
