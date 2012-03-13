/****************************************************************************
**
** Copyright (C) 2012 Jan M. Binder
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
