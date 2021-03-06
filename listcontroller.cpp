/****************************************************************************
**
** Copyright (C) 2011-2012 Jan M. Binder, Simeon Voelkel
** Contact: jan.binder@sfz-bw.de, simeon.voelkel@sfz-bw.de
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

#include "listcontroller.h"
#include <QFile>
#include <QStringList>
#include <QTextStream>
#include <QBrush>

ListController::ListController(QObject *parent) :
    QObject(parent)
{
    stlm = new StageListModel();
    currentIndex = 0;
}

ListController::~ListController(){
    delete stlm;
}

void ListController::forward(){
    QTime tmpt = QTime(0,0,0);
    if(currentIndex < stlm->rowCount()-1){
        currentIndex++;
        stlm->setHighlightedRow(currentIndex);
        Stage st = stlm->getList().value(currentIndex);
        Stage lastst = stlm->getList().value(currentIndex-1);
        if (!lastst.carry) {
            if (lastst.ocarry) {
                emit getElapsedOverTime();
            }
            else {
                emit resetTime();
            }
        }
        emit allowedTimeChanged(tmpt.msecsTo(st.duration));
        emit overTimeChanged(tmpt.msecsTo(st.overtime));
        emit stageNameChanged(st.name);
        emit roomClockChanged(st.roomclock);
    } else if (currentIndex >= stlm->rowCount()-1){
        emit endOfStage();
        currentIndex = stlm->rowCount()-1;
    }
}

void ListController::backward(){
    QTime tmpt = QTime(0,0,0);
    if(currentIndex > 0){
        currentIndex--;
        stlm->setHighlightedRow(currentIndex);
        Stage st = stlm->getList().value(currentIndex);
        if (!st.carry) emit resetTime();
        emit allowedTimeChanged(tmpt.msecsTo(st.duration));
        emit overTimeChanged(tmpt.msecsTo(st.overtime));
        emit stageNameChanged(st.name);
        emit roomClockChanged(st.roomclock);
    } else if (currentIndex <= 0){
        emit endOfStage();
        currentIndex = 0;
    }
}

void ListController::handleOvertime(int over){
    Stage st = stlm->getList().value(currentIndex);
    if (!st.autoadvance)
        return;

    forward();
    if (!st.carry && st.ocarry){
        emit elapsedTimeChanged(over);
    }
}

void ListController::setElapsedOverTime(int over){
    if (over < 0) over = 0;
    emit elapsedTimeChanged(over);
}

int ListController::loadListFromFile(QString path){
    QList<Stage> tmplist;
    QFile file(path);
    StageListModel* oldstlm;

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return 1;

    QTextStream in(&file);
    while (!in.atEnd()) {
        QTime tmpt = QTime(0,0,0);
        QString line = in.readLine();
        QStringList sl = line.split(QChar('\t'));
        if(sl.size() == 3){
            tmplist.append( Stage(
                                tmpt.addMSecs(sl.value(0).toInt()),
                                tmpt.addMSecs(sl.value(1).toInt()),
                                sl.value(2))
                            );
        }else if(sl.size() == 4){
            tmplist.append( Stage(
                                tmpt.addMSecs(sl.value(0).toInt()),
                                tmpt.addMSecs(sl.value(1).toInt()),
                                sl.value(2),
                                (sl.value(3).toUInt() > 0 ? true : false)
                                ) );
        }else if(sl.size() >= 7){
            tmplist.append( Stage(
                            tmpt.addMSecs(sl.value(0).toInt()),
                            tmpt.addMSecs(sl.value(1).toInt()),
                            sl.value(2),
                            (sl.value(3).toUInt() > 0 ? true : false),
                            (sl.value(4).toUInt() > 0 ? true : false),
                            (sl.value(5).toUInt() > 0 ? true : false),
                            (sl.value(6).toUInt() > 0 ? true : false)
                            ) );
        }else{
            // We read a comment line
        }
    }
    oldstlm = stlm;
    stlm = new StageListModel(tmplist);
    emit modelChanged(stlm);
    delete oldstlm;
    file.close();

    QTime tmpt = QTime(0,0,0);
    if(currentIndex < stlm->rowCount()-1){
        Stage st = stlm->getList().value(currentIndex);
        emit allowedTimeChanged(tmpt.msecsTo(st.duration));
        emit overTimeChanged(tmpt.msecsTo(st.overtime));
        emit stageNameChanged(st.name);
        emit roomClockChanged(st.roomclock);
    }
    return 0;
}

int ListController::saveListToFile(QString path){
    QTime tmpt = QTime(0,0,0);
    QList<Stage> tmplist = stlm->getList();
    QFile file(path);
         if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
             return 1;

    QTextStream out(&file);
    for(QList<Stage>::iterator t = tmplist.begin(); t != tmplist.end(); t++){
        out << tmpt.msecsTo(t->duration);
        out << "\t" << tmpt.msecsTo(t->overtime);
        out << "\t" << t->name;
        out << "\t" << (unsigned int)(t->autoadvance ? 1 : 0);
        out << "\t" << (unsigned int)(t->carry ? 1 : 0);
        out << "\t" << (unsigned int)(t->ocarry ? 1 : 0);
        out << "\t" << (unsigned int)(t->roomclock ? 1 : 0);
        out << "\n";
    }
    file.close();
    return 0;
}

QAbstractTableModel* ListController::getModel(){
    return stlm;
}

void ListController::add(){
    stlm->insertRows(stlm->rowCount(),1);
}

void ListController::del(QModelIndex ind){
    stlm->removeRows(ind.row(),1);
}

int ListController::getCurrentIndex(){
    return currentIndex;
}

int ListController::getMaxIndex(){
    return stlm->rowCount()-1;
}

void ListController::setCurrentIndex(int currentIndex){
    QTime tmpt = QTime(0,0,0);
    if(currentIndex >= 0 && currentIndex <= stlm->rowCount()-1){
        this->currentIndex = currentIndex;
        stlm->setHighlightedRow(currentIndex);
        Stage st = stlm->getList().value(currentIndex);
        emit allowedTimeChanged(tmpt.msecsTo(st.duration));
        emit overTimeChanged(tmpt.msecsTo(st.overtime));
        emit stageNameChanged(st.name);
        emit roomClockChanged(st.roomclock);
    }
}

void ListController::checkAutoStart(){
    if(currentIndex >= 0 && currentIndex <= stlm->rowCount()-1){
        Stage st = stlm->getList().value(currentIndex);
        if(st.roomclock){
            forward();
        }
    }
}
