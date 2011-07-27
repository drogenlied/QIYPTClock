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
    void setTime(int ms);
private:
    QGraphicsScene *nscene;
    //QSvgRenderer *renderer;
    //QGraphicsSvgItem *normal, *nbegin, *nend, *overtime, *obegin, *oend;
    QGraphicsEllipseItem *fg, *mg, *bg;
    int time, maxtime;
    void resizeEvent(QResizeEvent *event);
};

#endif
