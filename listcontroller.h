#ifndef LISTCONTROLLER_H
#define LISTCONTROLLER_H

#include <QObject>

class ListController : public QObject
{
    Q_OBJECT
public:
    explicit ListController(QObject *parent = 0);
    ~ListController();
    int loadListFromFile(QString path);

signals:
    void newAllowedTime(int);
    void resetTime();

public slots:
    void forward();
    void backward();
private:

};

#endif // LISTCONTROLLER_H
