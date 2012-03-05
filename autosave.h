#ifndef AUTOSAVE_H
#define AUTOSAVE_H

#include <QObject>

class AutoSave : public QObject
{
    Q_OBJECT
public:
    explicit AutoSave(QObject *parent = 0,MainWindow *mw, QString *dest);
    
signals:
    
public slots:
    void save();

private:
    MainWindow *mw;
    QString *dest;
};

#endif // AUTOSAVE_H
