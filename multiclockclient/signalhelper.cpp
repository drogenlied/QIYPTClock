#include "signalhelper.h"

SignalHelper::SignalHelper(QObject *parent) :
    QObject(parent)
{
}
SignalHelper::SignalHelper(QObject *parent, QString t) :
    QObject(parent)
{
    title = t;
}

void SignalHelper::fireSignal(int s){
}

QString SignalHelper::getTitle(){
    return title;
}
