#include "signalhelper.h"
#include <QTime>

SignalHelper::SignalHelper(QString t, QObject *parent) :
    QObject(parent)
{
      title = t;

      time = 0;
      allowedTime = 1;
      stageName = "";
}

SignalHelper::~SignalHelper(){
    qDebug("SignalHelper died");
}

void SignalHelper::fireSignal(quint32 ntime, quint32 nallowedTime, QString nstageName){
    if (time != ntime){
        time = ntime;
        emit timeUpdate(time);
        emit timeUpdate(this->toString());
    }
    if (allowedTime != nallowedTime){
        allowedTime = nallowedTime;
        emit allowedTimeChanged(allowedTime);
    }
    if (nstageName != stageName){
        stageName = nstageName;
        emit stageNameChanged(stageName);
    }
}

QString SignalHelper::getTitle(){
    return title;
}

QString SignalHelper::toString(){
    QTime tmp = QTime(0,0,0,0);
    tmp = tmp.addMSecs(time);
    QString s = tmp.toString("mm:ss");
    return s;
}
