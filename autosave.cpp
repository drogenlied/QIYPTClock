#include "autosave.h"

AutoSave::AutoSave(QObject *parent, MainWindow *mw, QString *dest) :
    QObject(parent)
{
    this->mw = mw;
    this->dest = dest;
}
void AutoSave::save()
{
    mw->lc->
}
