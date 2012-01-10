#ifndef QRESIZABLELABEL_H
#define QRESIZABLELABEL_H

#include <QLabel>

class QResizableLabel : public QLabel
{
    Q_OBJECT
public:
    explicit QResizableLabel(QWidget *parent = 0, Qt::WindowFlags f = 0);
    explicit QResizableLabel( const QString text, QWidget * parent = 0, Qt::WindowFlags f = 0 );

signals:

public slots:

};

#endif // QRESIZABLELABEL_H
