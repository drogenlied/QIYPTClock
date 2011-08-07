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

StageListModel::StageListModel(QObject *parent)
     : QAbstractTableModel(parent)
 {
 }

 StageListModel::StageListModel(QList< QPair<QTime, QString> > pairs, QObject *parent)
     : QAbstractTableModel(parent)
 {
     listOfStages=pairs;
 }

 int StageListModel::rowCount(const QModelIndex &parent) const
 {
     Q_UNUSED(parent);
     return listOfStages.size();
 }

 int StageListModel::columnCount(const QModelIndex &parent) const
 {
     Q_UNUSED(parent);
     return 2;
 }

 QVariant StageListModel::data(const QModelIndex &index, int role) const
 {
     if (!index.isValid())
         return QVariant();

     if (index.row() >= listOfStages.size() || index.row() < 0)
         return QVariant();

     if (role == Qt::DisplayRole) {
         QPair<QTime, QString> pair = listOfStages.at(index.row());

         if (index.column() == 0)
             return pair.first;
         else if (index.column() == 1)
             return pair.second;
     }
     return QVariant();
 }

 QVariant StageListModel::headerData(int section, Qt::Orientation orientation, int role) const
 {
     if (role != Qt::DisplayRole)
         return QVariant();

     if (orientation == Qt::Horizontal) {
         switch (section) {
             case 0:
                 return tr("Duration");

             case 1:
                 return tr("Stage Name");

             default:
                 return QVariant();
         }
     }
     return QVariant();
 }

 bool StageListModel::insertRows(int position, int rows, const QModelIndex &index)
 {
     Q_UNUSED(index);
     beginInsertRows(QModelIndex(), position, position+rows-1);

     for (int row=0; row < rows; row++) {
         QPair<QTime, QString> pair(QTime(0,0,1), " ");
         listOfStages.insert(position, pair);
     }

     endInsertRows();
     return true;
 }

 bool StageListModel::removeRows(int position, int rows, const QModelIndex &index)
 {
     Q_UNUSED(index);
     beginRemoveRows(QModelIndex(), position, position+rows-1);

     for (int row=0; row < rows; ++row) {
         listOfStages.removeAt(position);
     }

     endRemoveRows();
     return true;
 }

 bool StageListModel::setData(const QModelIndex &index, const QVariant &value, int role)
 {
         if (index.isValid() && role == Qt::EditRole) {
                 int row = index.row();

                 QPair<QTime, QString> p = listOfStages.value(row);

                 if (index.column() == 0)
                         p.first = value.toTime();
                 else if (index.column() == 1)
                         p.second = value.toString();
         else
             return false;

         listOfStages.replace(row, p);
                 emit(dataChanged(index, index));

         return true;
         }

         return false;
 }

 Qt::ItemFlags StageListModel::flags(const QModelIndex &index) const
 {
     if (!index.isValid())
         return Qt::ItemIsEnabled;

     return QAbstractTableModel::flags(index) | Qt::ItemIsEditable;
 }

 QList< QPair<QTime, QString> > StageListModel::getList()
 {
     return listOfStages;
 }
