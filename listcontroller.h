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

#ifndef LISTCONTROLLER_H
#define LISTCONTROLLER_H

#include <QObject>
#include "stagelistmodel.h"

class ListController : public QObject
{
    Q_OBJECT
public:
    explicit ListController(QObject *parent = 0);
    ~ListController();

    int loadListFromFile(QString path);
    int saveListToFile(QString path);
    QAbstractTableModel* getModel();

signals:
    void allowedTimeChanged(int);
    void resetTime();
    void stageNameChanged(QString);
    void modelChanged(QAbstractTableModel*);

public slots:
    void forward();
    void backward();
    void add();
    void del(QModelIndex ind);

private:
    StageListModel* stlm;
};

#endif // LISTCONTROLLER_H
