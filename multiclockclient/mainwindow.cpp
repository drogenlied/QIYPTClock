#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QVBoxLayout>
#include <QLCDNumber>
#include <QLabel>
#include "../themeclockwidget.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    grid = new QGridLayout(ui->centralWidget);
    ui->centralWidget->setLayout(grid);

    timer = new QTimer();


    m = new MultiBroadcastClient();
    connect(m, SIGNAL(newClock(SignalHelper*)), this, SLOT(createClock(SignalHelper*)));
    m->loadFromFile("fights.txt");
    elementNr = 0;
    timer->start(1000);
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
    QLabel *l = new QLabel(sh->getTitle());
    QLabel *t = new QLabel("Fight has not begun yet.");
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
