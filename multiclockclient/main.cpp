#include <QApplication>
#include <QCommandLineParser>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    bool noairport = false;

    QApplication a(argc, argv);
    QApplication::setApplicationName("multiclockclient");
    QApplication::setApplicationVersion("1.0");

    QCommandLineParser parser;
    parser.setApplicationDescription("Test helper");

    QCommandLineOption noairportOption(QStringList() << "a" << "noairport",
                                      QCoreApplication::translate("main", "disable configuration file"));

    parser.addHelpOption();
    parser.addVersionOption();
    parser.addOption(noairportOption);
    parser.process(a);

    noairport = parser.isSet(noairportOption);

    MainWindow w(noairport);
    //qDebug("show dat stuff");
    w.show();
    //qDebug("now exec!");
    int ret = a.exec();
    qDebug("Finished.");
    return ret;
}
