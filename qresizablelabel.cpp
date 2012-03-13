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

#include "qresizablelabel.h"

QResizableLabel::QResizableLabel(QWidget *parent, Qt::WindowFlags f) :
    QLabel(parent, f)
{
}
QResizableLabel::QResizableLabel( const QString text, QWidget * parent, Qt::WindowFlags f) :
    QLabel(text, parent, f)
{
}

