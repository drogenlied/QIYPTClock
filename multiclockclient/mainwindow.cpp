#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QLCDNumber>
#include <QLabel>
#include <QFile>
#include <QFont>
#include "../themeclockwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    timer = new QTimer();
    elementNr = 0;
    ui->setupUi(this);
    grid = new QGridLayout();
    ui->centralWidget->setLayout(grid);

    m = new MultiBroadcastClient();
    connect(m, SIGNAL(newClock(SignalHelper*)), this, SLOT(createClock(SignalHelper*)));

    if (QFile("fights.txt").exists()){
        m->loadFromFile("fights.txt");
    } else if (QFile("/usr/share/iyptclock/fights.txt").exists()){
        m->loadFromFile("/usr/share/iyptclock/fights.txt");
    } else {
       qWarning("No valid configuration found");
       QApplication::quit();
    }

    timer->start(1000);
    //qDebug("mainwindow finished");
}

MainWindow::~MainWindow()
{
    delete m;
    delete grid;
    delete ui;
}


void MainWindow::createClock(SignalHelper* sh){
    //qDebug("New clock: %s\n", sh->getTitle().toStdString().c_str());
    QVBoxLayout *b = new QVBoxLayout();
    ThemeClockWidget *w = new ThemeClockWidget();
    w->setRenderHint(QPainter::Antialiasing);
    QLabel *l = new QLabel(sh->getTitle());
    QFont f = l->font();
    f.setBold(true);
    f.setPointSize(15);
    l->setFont(f);
    QLabel *t = new QLabel("Fight has not begun yet.");
    f = t->font();
    f.setPointSize(12);
    t->setFont(f);
    QLCDNumber *n = new QLCDNumber(5);
    n->setSegmentStyle(QLCDNumber::Flat);

    connect(sh, SIGNAL(timeUpdate(int)), w, SLOT(setTime(int)));
    connect(sh, SIGNAL(timeUpdate(QString)), n, SLOT(display(QString)));
    connect(sh, SIGNAL(stageNameChanged(QString)), t, SLOT(setText(QString)));
    connect(sh, SIGNAL(allowedTimeChanged(int)), w,SLOT(setAllowedTime(int)));
    connect(timer, SIGNAL(timeout()), w, SLOT(act()));

    b->addWidget(l);
    b->addWidget(t);
    b->addWidget(w);
    b->addWidget(n);
    grid->addLayout(b, elementNr /4, elementNr%4, 1, 1);
    elementNr++;
}
