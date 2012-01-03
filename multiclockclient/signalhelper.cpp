#include "signalhelper.h"

SignalHelper::SignalHelper(QObject *parent) :
    QObject(parent)
{
}

void SignalHelper<X>::fireSignal(unsigned int s){
    emit sig(s);
}
