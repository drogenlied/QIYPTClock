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

ListController::ListController(QObject *parent) :
    QObject(parent)
{
}

ListController::~ListController(){

}

void ListController::forward(){

}

void ListController::backward(){

}

int ListController::loadListFromFile(QString path){
    return 0;
}

int ListController::saveListToFile(QString path){
    return 0;
}
