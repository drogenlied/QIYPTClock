#include <QtGui/QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    //qDebug("show dat stuff");
    w.show();
    //qDebug("now exec!");
    int ret = a.exec();
    qDebug("Finished.");
    return ret;
}
