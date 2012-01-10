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

#include "themeclockwidget.h"
#include <cmath>

ThemeClockWidget::ThemeClockWidget(QWidget *parent) :
    QGraphicsView(parent)
{
    nscene = new QGraphicsScene();
    setScene(nscene);

    //renderer = new QSvgRenderer(QLatin1String("blub.svg"));

    fg = new QGraphicsEllipseItem(0,0,300,300);
    fg->setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
    fg->setStartAngle(90*16);
    fg->setSpanAngle(-50*16);
    fg->setBrush(QBrush(QColor(100,30,100)));
    fg->setPen(QPen(QColor(0,0,0,0)));

    mg = new QGraphicsEllipseItem(0,0,300,300);
    mg->setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
    mg->setStartAngle(90*16);
    mg->setSpanAngle(-5*16);
    mg->setBrush(QBrush(QColor(200,0,0)));
    mg->setPen(QPen(QColor(0,0,0,0)));


    bg = new QGraphicsEllipseItem(0,0,300,300);
    bg->setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
    bg->setStartAngle(90*16);
    bg->setSpanAngle(-130*16);
    bg->setBrush(QBrush(QColor(50,200,30)));
    bg->setPen(QPen(QColor(0,0,0,0)));

    focus = new QGraphicsEllipseItem(0,0,300,300);
    focus->setPen(QPen(QColor(0,0,0,0)));


    time = 0;
    maxtime = 1;

/*
    normal = new QGraphicsSvgItem();
    nbegin = new QGraphicsSvgItem();
    nend = new QGraphicsSvgItem();
    overtime = new QGraphicsSvgItem();
    obegin = new QGraphicsSvgItem();
    oend = new QGraphicsSvgItem();

    normal->setSharedRenderer(renderer);
    normal->setElementId(QLatin1String("normal"));
    normal->setParentItem(bg);

    nbegin->setSharedRenderer(renderer);
    nbegin->setElementId(QLatin1String("normal-begin"));
    nbegin->setParentItem(normal);

    nend->setSharedRenderer(renderer);
    nend->setElementId(QLatin1String("normal-end"));
    nend->setParentItem(normal);

    overtime->setSharedRenderer(renderer);
    overtime->setElementId(QLatin1String("overtime"));
    overtime->setParentItem(fg);

    obegin->setSharedRenderer(renderer);
    obegin->setElementId(QLatin1String("overtime-begin"));
    obegin->setParentItem(overtime);

    oend->setSharedRenderer(renderer);
    oend->setElementId(QLatin1String("overtime-end"));
    oend->setParentItem(overtime);
*/
    scene()->addItem(focus);
    scene()->addItem(bg);
    scene()->addItem(mg);
    scene()->addItem(fg);
}

ThemeClockWidget::~ThemeClockWidget() {
    delete nscene;

    /*delete normal;
    delete nbegin;
    delete nend;
    delete overtime;
    delete obegin;
    delete oend;

    delete renderer;
    */

    delete focus;
    delete bg;
    delete mg;
    delete fg;
    qDebug("ThemeClockWidget died");
}

void ThemeClockWidget::resizeEvent(QResizeEvent *event){
    this->fitInView(focus, Qt::KeepAspectRatio);
    this->centerOn(focus);
}

void ThemeClockWidget::act(){
    //qDebug("Acting");
    bg->setSpanAngle(-round(((double)time*360*16)/(double)maxtime));

    if(time < maxtime/6*5) // over 5/6 of time left
    {
        bg->setBrush(QBrush(QColor(50,200,30)));
    }
    else
    {
        bg->setBrush(QBrush(QColor(255,190,30)));
    }


    if(time > maxtime && time < 2*maxtime){
        mg->setSpanAngle(-round((((double)time-maxtime)*360*16)/(double)maxtime));
    } else if (time > 2*maxtime){
        mg->setSpanAngle(360*16);
    }else{
        mg->setSpanAngle(0);
    }
    if(time>2*maxtime){
        fg->setSpanAngle(-round((((double)time-2*(double)maxtime)*360*16)/(double)maxtime));
    }else{
        fg->setSpanAngle(0);
    }
}

void ThemeClockWidget::setAllowedTime(int ms){
    if(ms>0){
        maxtime = ms;
    }
    //act();
}

void ThemeClockWidget::setTime(int ms){
    time = ms;
    //act();
}

int ThemeClockWidget::getTime(){
    return time;
}

int ThemeClockWidget::getAllowedTime(){
    return maxtime;
}
