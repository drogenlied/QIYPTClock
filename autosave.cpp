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
