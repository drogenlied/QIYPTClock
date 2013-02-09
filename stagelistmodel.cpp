/****************************************************************************
 **
 ** Copyright (C) 2009 Nokia Corporation and/or its subsidiary(-ies).
 ** Contact: Qt Software Information (qt-info@nokia.com)
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

#include "stagelistmodel.h"

Stage::Stage(){

}

Stage::Stage(QTime d, QTime o, QString n, bool a, bool c, bool oc, bool r){
    duration = d;
    overtime = o;
    name = n;
    autoadvance = a;
    carry = c;
    ocarry = oc;
    roomclock = r;
}

StageListModel::StageListModel(QObject *parent)
     : QAbstractTableModel(parent)
 {
    highlightedRow = 0;
    highlightColor = QColor::fromRgb(0xff, 0x99, 0x11);
 }

StageListModel::StageListModel(QList<Stage> stages, QObject *parent)
    : QAbstractTableModel(parent) {
    listOfStages=stages;
    highlightColor = QColor::fromRgb(0xff, 0x99, 0x11);
    highlightedRow = 0;
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
            return stage.duration.toString("mm:ss");
        else if (index.column() == 1)
            return stage.overtime.toString("mm:ss");
        else if (index.column() == 2)
            return stage.name;
        else if (index.column() == 3)
            return stage.carry;
        else if (index.column() == 4)
            return stage.carry;
        else if (index.column() == 5)
            return stage.ocarry;
        else if (index.column() == 6)
            return stage.roomclock;
    }
    if (role == Qt::BackgroundRole) {
        if(index.row() == highlightedRow)
            return highlightColor;
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
                return tr("Overtime");
            case 2:
                return tr("Stage Description");
            case 3:
                return tr("Autoadvance");
            case 4:
                return tr("Carry Time");
            case 5:
                return tr("Carry Overtime");
            case 6:
                return tr("Room Clock");
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
        Stage stage(QTime(0,0,1), QTime(0,0,0), " ");
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
        Stage p = listOfStages.value(row);
        if (index.column() == 0)
            p.duration = QTime::fromString(value.toString(), "mm:ss");
        else if (index.column() == 1)
            p.overtime = QTime::fromString(value.toString(), "mm:ss");
        else if (index.column() == 2)
            p.name = value.toString();
        else if (index.column() == 3)
            p.autoadvance = value.toBool();
        else if (index.column() == 4)
            p.carry = value.toBool();
        else if (index.column() == 5)
            p.ocarry = value.toBool();
        else if (index.column() == 6)
            p.roomclock = value.toBool();
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
    return QAbstractTableModel::flags(index) | Qt::ItemIsEditable | Qt::ItemIsDragEnabled | Qt::ItemIsDropEnabled;
}

QList<Stage> StageListModel::getList(){
    return listOfStages;
}

int StageListModel::getHighlightedRow(){
    return highlightedRow;
}

void StageListModel::setHighlightedRow(int row){
    if (row < listOfStages.size() && row >= 0){
        int tlRow = (row < highlightedRow) ? row : highlightedRow;
        int brRow = (row < highlightedRow) ? highlightedRow : row;
        highlightedRow = row;
        emit dataChanged(this->index(tlRow,0),this->index(brRow,this->columnCount()-1));
    }
}

QColor StageListModel::getHighlightColor(){
    return highlightColor;
}

void StageListModel::setHighlightColor(QColor color){
    highlightColor = color;
    emit dataChanged(this->index(highlightedRow,0),this->index(highlightedRow,this->columnCount()-1));
}

Qt::DropActions StageListModel::supportedDropActions() const {
    return Qt::CopyAction | Qt::MoveAction;
}
