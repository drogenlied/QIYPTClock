/****************************************************************************
**
** Copyright (C) 2011-2012 Jan M. Binder, Felix Engelmann, Simeon Voelkel
** Contact: jan.binder@sfz-bw.de, felix.engelmann@sfz-bw.de,
**          simeon.voelkel@sfz-bw.de
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
    int getMaxIndex();
    int getCurrentIndex();
    void setCurrentIndex(int currentIndex);
    QAbstractTableModel* getModel();

signals:
    void allowedTimeChanged(int);
    void elapsedTimeChanged(int);
    void overTimeChanged(int);
    void resetTime();
    void stageNameChanged(QString);
    void modelChanged(QAbstractTableModel*);
    void endOfStage();
    void roomClockChanged(bool);
    void getElapsedOverTime();

public slots:
    void forward();
    void backward();
    void handleOvertime(int);
    void add();
    void del(QModelIndex ind);
    void checkAutoStart();
    void setElapsedOverTime(int);

private:
    StageListModel* stlm;
    int currentIndex;
};

#endif // LISTCONTROLLER_H
