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

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QAbstractTableModel>
#include <QtCore/QTimer>
#include "aboutdialog.h"
#include "autosave.h"
#include "broadcastserver.h"
#include "listcontroller.h"
#include "themeclock.h"


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
    void toggleTimeSpinBox();
    void saveStages();
    void setTime();
    void propagateModel(QAbstractTableModel*);
    void setLcdWidthForTime(int);

signals:
    void newID(unsigned int);
    void newPort(unsigned int);
    void itemShouldBeDeleted(QModelIndex);

protected:
    void changeEvent(QEvent *e);

friend class AutoSave;
private:
    Ui::MainWindow *ui;
    AboutDialog *ad;
    QTimer *timer, *timer2, *timer3;
    ThemeClock *thc;
    ListController *lc;
    BroadcastServer *bs;
    QString savefile;
    AutoSave *as;
    enum {
        TIME_SAVED,
        TIME_ELAPSED,
        TIME_LEFT
    };
};

#endif // MAINWINDOW_H
