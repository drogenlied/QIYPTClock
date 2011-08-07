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

#ifndef STAGELISTMODEL_H
#define STAGELISTMODEL_H

#include <QAbstractTableModel>
#include <QList>
#include <QTime>

class Stage {
public:
    Stage();
    Stage(QTime duration, QString name, bool carry = false);

    QTime duration;
    QString name;
    bool carry;
};

class StageListModel : public QAbstractTableModel
{
    Q_OBJECT

public:
    StageListModel(QObject *parent=0);
    StageListModel(QList<Stage> listofStages, QObject *parent=0);

    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role=Qt::EditRole);
    bool insertRows(int position, int rows, const QModelIndex &index=QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index=QModelIndex());
    QList<Stage> getList();

private:
    QList<Stage> listOfStages;
};

#endif // STAGELISTMODEL_H
