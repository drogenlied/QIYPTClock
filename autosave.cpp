/****************************************************************************
**
** Copyright (C) 2012 Felix Engelmann, Simeon Voelkel
** Contact: felix.engelmann@sfz-bw.de, simeon.voelkel@sfz-bw.de
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

#include <QFile>
#include <QtConcurrentRun>

#include "autosave.h"
#include "listcontroller.h"
#include "themeclock.h"
#include "mainwindow.h"

AutoSave::AutoSave(MainWindow *mw, QString dest, QObject *parent) :
    QObject(parent)
{
    this->mw = mw;
    this->dest = dest;
    this->lastsavedtime = 0;
}
void AutoSave::writeToDisk(int step, int time)
{
    QFile file(dest);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
        return;

    QTextStream out(&file);
    out << step << "\n" << time << "\n";

    file.close();
}

void AutoSave::save()
{
    int current = mw->lc->getCurrentIndex();
    int time = mw->thc->getElapsedTime();
    if ( time/1000 > 15 ){ // only save times larger than 20s (this allows to revert a double-skip)
        lastsavedtime = mw->thc->getElapsedTime();
    }
    QtConcurrent::run(this, &AutoSave::writeToDisk, current, time);
}

void AutoSave::load()
{
    QFile file(dest);
    if (!file.exists()) return;
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) return;

    QTextStream in(&file);
    QString line;
    int step=0, time=0;

    if (in.atEnd()) {
        file.close();
        return;
    }
    line = in.readLine();
    step = line.toInt();

    if (in.atEnd()) {
        file.close();
        return;
    }
    line = in.readLine();
    time = line.toInt();

    file.close();

    if (step != mw->lc->getMaxIndex()){ // load autosave only if last stage wasn't finished
        mw->lc->setCurrentIndex(step);
        mw->thc->setElapsedTime(time);
    }
}

int AutoSave::getLastSavedTime()
{
  return lastsavedtime;
}


