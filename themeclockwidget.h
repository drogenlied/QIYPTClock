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

#ifndef THEMECLOCKWIDGET_H
#define THEMECLOCKWIDGET_H

#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsScene>
#include <QtSvg/QSvgRenderer>
#include <QtSvg/QGraphicsSvgItem>
#include <QtGui/QGraphicsEllipseItem>

class ThemeClockWidget : public QGraphicsView
{
    Q_OBJECT

public:
    ThemeClockWidget(QWidget *parent = 0);
    ~ThemeClockWidget();
    int getTime();
    int getAllowedTime();
public slots:
    void act();
    void setAllowedTime(int ms);
    void setRoomclock(bool roomclock);
    void setTime(int ms);
private:
    QGraphicsScene *nscene;
    QGraphicsScene *rscene;
    QGraphicsRectItem *hourHand;
    QGraphicsRectItem *minuteHand;
    //QGraphicsRectItem *secondHand;
    QGraphicsPolygonItem *secondHand;
    QGraphicsPolygonItem *secondHandBase;
    QGraphicsEllipseItem *secondRing;
    //QSvgRenderer *renderer;
    //QGraphicsSvgItem *normal, *nbegin, *nend, *overtime, *obegin, *oend;
    QGraphicsEllipseItem *fg, *mg, *bg, *focus, *focus2;
    int time, maxtime;
    bool roomclock;
    void actRoomclock();
    void actCake();
    bool isRoomclock();
    void resizeEvent(QResizeEvent *event);
};

#endif
