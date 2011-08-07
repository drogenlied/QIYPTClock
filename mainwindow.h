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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractTableModel>
#include "themeclock.h"
#include "listcontroller.h"
#include "broadcastserver.h"
#include <QtCore/QTimer>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void triggerId();
    void triggerPort();
    void triggerDel();
    void toggleStartPause();
    void saveStages();
    void propagateModel(QAbstractTableModel*);

signals:
    void newID(unsigned int);
    void newPort(unsigned int);
    void itemShouldBeDeleted(QModelIndex);

protected:
    void changeEvent(QEvent *e);

private:
    Ui::MainWindow *ui;
    QTimer *timer, *timer2;
    ThemeClock *thc;
    ListController *lc;
    BroadcastServer *bs;

};

#endif // MAINWINDOW_H
