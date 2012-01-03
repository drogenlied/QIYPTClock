#include "signalhelper.h"

SignalHelper::SignalHelper(QObject *parent) :
    QObject(parent)
{
}

void SignalHelper::fireSignal(int s){
    emit sig(s);
}
