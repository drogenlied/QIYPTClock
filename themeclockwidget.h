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

#ifndef THEMECLOCKWIDGET_H
#define THEMECLOCKWIDGET_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QSvgRenderer>
#include <QGraphicsSvgItem>
#include <QGraphicsEllipseItem>

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

    QGraphicsPolygonItem *hourHand;
    QGraphicsPolygonItem *minuteHand;
    QGraphicsPolygonItem *secondHand;
    QGraphicsPolygonItem *secondHandBase;
    QGraphicsEllipseItem *secondRing;

    QGraphicsEllipseItem *fg, *mg, *bg, *ring, *focus, *focus2;
    int time, maxtime;
    bool roomclock;

    void actRoomclock();
    void actCake();
    bool isRoomclock();
    void resizeEvent(QResizeEvent *event);
};

#endif
