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

#include "listcontroller.h"
#include <QFile>
#include <QStringList>
#include <QTextStream>

ListController::ListController(QObject *parent) :
    QObject(parent)
{
    stlm = new StageListModel();
}

ListController::~ListController(){

}

void ListController::forward(){

}

void ListController::backward(){

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
        if(sl.size() == 2){
            tmplist.append( Stage(
                                tmpt.addMSecs(sl.value(0).toInt()),
                                sl.value(1))
                            );
        }else if(sl.size() >= 3){
            tmplist.append( Stage(
                                tmpt.addMSecs(sl.value(0).toInt()),
                                sl.value(1),
                                (sl.value(3).toUInt() > 0 ? true : false)
                                ) );
        }
    }
    oldstlm = stlm;
    stlm = new StageListModel(tmplist);
    emit modelChanged(stlm);
    delete oldstlm;
    file.close();
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
        out << tmpt.msecsTo(t->duration) << "\t" << t->name << "\t" << (unsigned int)(t->carry ? 1 : 0) << "\n";
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
