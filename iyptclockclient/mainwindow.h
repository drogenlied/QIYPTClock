/****************************************************************************
**
** Copyright (C) 2011-2012 Jan M. Binder
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

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(unsigned int port, unsigned int sig, QWidget *parent = nullptr);
    ~MainWindow();

public slots:
//    void triggerId();
//    void triggerPort();
    void setLcdWidthForTime(int);

signals:
    void newID(unsigned int);
    void newPort(unsigned int);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
