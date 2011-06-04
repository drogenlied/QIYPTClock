#include "themeclockwidget.h"

ThemeClockWidget::ThemeClockWidget(QWidget *parent) :
    QGraphicsView(parent)
{
    scene = new QGraphicsScene();
    setScene(scene);

    renderer = new QSvgRenderer(QLatin1String("blub.svg"));

    normal = new QGraphicsSvgItem();
    nbegin = new QGraphicsSvgItem();
    nend = new QGraphicsSvgItem();
    overtime = new QGraphicsSvgItem();
    obegin = new QGraphicsSvgItem();
    oend = new QGraphicsSvgItem();

    normal->setSharedRenderer(renderer);
    normal->setElementId(QLatin1String("normal"));

    nbegin->setSharedRenderer(renderer);
    nbegin->setElementId(QLatin1String("normal-begin"));

    nend->setSharedRenderer(renderer);
    nend->setElementId(QLatin1String("normal-end"));

    overtime->setSharedRenderer(renderer);
    overtime->setElementId(QLatin1String("overtime"));

    obegin->setSharedRenderer(renderer);
    obegin->setElementId(QLatin1String("overtime-begin"));

    oend->setSharedRenderer(renderer);
    oend->setElementId(QLatin1String("overtime-end"));

    scene->addItem(normal);
    scene->addItem(nbegin);
    scene->addItem(nend);
    scene->addItem(overtime);
    scene->addItem(obegin);
    scene->addItem(oend);
}

ThemeClockWidget::~ThemeClockWidget() {
    delete scene;

    delete normal;
    delete nbegin;
    delete nend;
    delete overtime;
    delete obegin;
    delete oend;

    delete renderer;
}
