#ifndef AUTOSAVE_H
#define AUTOSAVE_H

#include <QObject>

class MainWindow;

class AutoSave : public QObject
{
    Q_OBJECT
public:
    explicit AutoSave(MainWindow *mw, QString dest, QObject *parent = 0);
    void load();
    
signals:
    
public slots:
    void save();

private:
    MainWindow *mw;
    QString dest;
    void writeToDisk(int step, int time);
};

#endif // AUTOSAVE_H
