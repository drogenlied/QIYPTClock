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
    fg->setBrush(QBrush(QColor(255,0,0)));

    mg = new QGraphicsEllipseItem(0,0,300,300);
    mg->setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
    mg->setStartAngle(90*16);
    mg->setSpanAngle(-5*16);
    mg->setBrush(QBrush(QColor(255,99,0)));

    bg = new QGraphicsEllipseItem(0,0,300,300);
    bg->setFlag(QGraphicsItem::ItemClipsChildrenToShape, true);
    bg->setStartAngle(90*16);
    bg->setSpanAngle(-130*16);
    bg->setBrush(QBrush(QColor(0,255,0)));

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

    delete bg;
    delete mg;
    delete fg;
}

void ThemeClockWidget::resizeEvent(QResizeEvent *event){
    this->centerOn(bg);
    //this->fitInView(bg);
}

void ThemeClockWidget::act(){
    bg->setSpanAngle(-((time*360*16)/maxtime));

    if(time > maxtime && time < 2*maxtime){
        mg->setSpanAngle(-(((time-maxtime)*360*16)/maxtime));
    } else if (time > 2*maxtime){
        mg->setSpanAngle(360*16);
    }else{
        mg->setSpanAngle(0);
    }
    if(time>2*maxtime){
        fg->setSpanAngle(-(((time-2*maxtime)*360*16)/maxtime));
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
