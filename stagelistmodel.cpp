/****************************************************************************
 **
 ** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
 ** Contact: Qt Software Information (qt-info@nokia.com)
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

#include "stagelistmodel.h"

Stage::Stage(){

}

Stage::Stage(QTime d, QString n, bool c){
    duration = d;
    name = n;
    carry = c;
}

StageListModel::StageListModel(QObject *parent)
     : QAbstractTableModel(parent)
 {
 }

StageListModel::StageListModel(QList<Stage> stages, QObject *parent)
    : QAbstractTableModel(parent) {
    listOfStages=stages;
}

int StageListModel::rowCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return listOfStages.size();
}

int StageListModel::columnCount(const QModelIndex &parent) const {
    Q_UNUSED(parent);
    return 2;
}

QVariant StageListModel::data(const QModelIndex &index, int role) const {
    if (!index.isValid())
        return QVariant();

    if (index.row() >= listOfStages.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        Stage stage = listOfStages.at(index.row());

        if (index.column() == 0)
            return stage.duration;
        else if (index.column() == 1)
            return stage.name;
        else if (index.column() == 2)
            return stage.carry;
    }
    return QVariant();
}

QVariant StageListModel::headerData(int section, Qt::Orientation orientation, int role) const {
    if (role != Qt::DisplayRole)
        return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Duration");
             case 1:
                return tr("Stage Description");
             case 2:
                return tr("Carry Time");
             default:
                return QVariant();
        }
    }
    return QVariant();
}

bool StageListModel::insertRows(int position, int rows, const QModelIndex &index) {
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position+rows-1);

    for (int row=0; row < rows; row++) {
        Stage stage(QTime(0,0,1), " ");
        listOfStages.insert(position, stage);
    }

    endInsertRows();
    return true;
}

bool StageListModel::removeRows(int position, int rows, const QModelIndex &index) {
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position+rows-1);

    for (int row=0; row < rows; ++row) {
        listOfStages.removeAt(position);
    }

    endRemoveRows();
    return true;
}

bool StageListModel::setData(const QModelIndex &index, const QVariant &value, int role) {
    if (index.isValid() && role == Qt::EditRole) {
        int row = index.row();
        QTime tmpt = QTime(0,0,0);
        Stage p = listOfStages.value(row);
        if (index.column() == 0)
            p.duration = tmpt.addSecs(value.toInt());
        else if (index.column() == 1)
            p.name = value.toString();
        else if (index.column() == 2)
            p.carry = value.toBool();
        else
            return false;

        listOfStages.replace(row, p);
        emit(dataChanged(index, index));

        return true;
    }
    return false;
}

Qt::ItemFlags StageListModel::flags(const QModelIndex &index) const {
    if (!index.isValid())
        return Qt::ItemIsEnabled;
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
}

QList<Stage> StageListModel::getList(){
    return listOfStages;
}
