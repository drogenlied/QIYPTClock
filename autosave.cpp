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
