#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QGraphicsScene"
#include "QGraphicsView"
#include "QGraphicsPixmapItem"
#include "QPushButton"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // Setup the background image of teh DENAS machine and draw to scene
    scene = new QGraphicsScene();
    // Load the image from the resource.qrc file
    QPixmap m(":/denas.png");
    scene->setBackgroundBrush(m);
    ui->graphicsView->setScene(scene);

    // Create the button, make "this" the parent and blank
    powerBtn = new QPushButton("", this);
    // set size and location of the button
    powerBtn->setGeometry(QRect(QPoint(130, 625), QSize(50, 50)));

    // Connect button signal to appropriate slot
    connect(powerBtn, SIGNAL (released()), this, SLOT (handlePowerButton()));
}

MainWindow::~MainWindow()
{
    // clean up the image and button
    delete scene;
    delete powerBtn;
    delete ui;
    delete centralProccess;
}

void MainWindow::handlePowerButton()
{
    // example of what happens when btn is pressed, we want this to call
    // the CentralProccess class and startup the display and whatever else
    centralProccess->initialize();
}

