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
    unsigned int port = 54545;
    unsigned int sig = 123456;

    QApplication a(argc, argv);
    QApplication::setApplicationName("iyptclockclient");
    QApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Test helper");

    QCommandLineOption portOption(QStringList() << "p" << "port",
                                  QCoreApplication::translate("main", "Port to listen on"),
                                  QCoreApplication::translate("main", "port"));

    QCommandLineOption signatureOption(QStringList() << "s" << "signature",
                                       QCoreApplication::translate("main", "Signature to use"),
                                       QCoreApplication::translate("main", "signature"));

    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOption(portOption);
    parser.addOption(signatureOption);
    parser.process(a);

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

    MainWindow w(port, sig);
    w.show();

    return a.exec();
}
