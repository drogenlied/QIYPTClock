#include "qresizablelabel.h"

QResizableLabel::QResizableLabel(QWidget *parent, Qt::WindowFlags f) :
    QLabel(parent, f)
{
}
QResizableLabel::QResizableLabel( const QString text, QWidget * parent, Qt::WindowFlags f) :
    QLabel(text, parent, f)
{
}

