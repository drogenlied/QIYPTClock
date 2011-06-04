#ifndef THEMECLOCKWIDGET_H
#define THEMECLOCKWIDGET_H

#include <QtGui/QGraphicsView>
#include <QtGui/QGraphicsScene>
#include <QtSvg/QSvgRenderer>
#include <QtSvg/QGraphicsSvgItem>

class ThemeClockWidget : public QGraphicsView
{
    Q_OBJECT

public:
    ThemeClockWidget(QWidget *parent = 0);
    ~ThemeClockWidget();
private:
    QGraphicsScene *scene;
    QSvgRenderer *renderer;
    QGraphicsSvgItem *normal, *nbegin, *nend, *overtime, *obegin, *oend;
};

#endif
