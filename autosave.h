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

#ifndef AUTOSAVE_H
#define AUTOSAVE_H

#include <QObject>
#include <QFuture>

class MainWindow;

class AutoSave : public QObject
{
    Q_OBJECT
public:
    AutoSave(MainWindow *mw, QString dest, QObject *parent = 0);
    void load();
    int getLastSavedTime();
    
signals:
    
public slots:
    void save();

private:
    MainWindow *mw;
    QString dest;
    int lastsavedtime;
    QFuture<void> saveJob;
};

#endif // AUTOSAVE_H
