#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QGraphicsScene"
#include "QGraphicsView"
#include "QGraphicsPixmapItem"
#include "QPushButton"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , mainMenu(QStringList())
    , programsMenu(QStringList())
    , frequencyMenu(QStringList())
    , mainMenuNode(nullptr,&mainMenu)
    , programsMenuNode(&mainMenuNode, &programsMenu)
    , frequencyMenuNode(&mainMenuNode, &frequencyMenu)
    , u()
    , menuData(QHash<QString, Node>())
    , programsData(QHash<QString, QString>())
    , frequencyData(QHash<QString, QString>())
{

    ui->setupUi(this);  
    // Setup the background image of teh DENAS machine and draw to scene
    scene = new QGraphicsScene();
    // Load the image from the resource.qrc file
    QPixmap m(":/images/denas.png");
    scene->setBackgroundBrush(m);
    ui->graphicsView->setScene(scene);
    ui->powerLevelProgBar->setValue(powerLevel);

    // Create the button, make "this" the parent and blank
    powerBtn = new QPushButton("", this);
    // set size and location of the button
    powerBtn->setGeometry(QRect(QPoint(130, 625), QSize(50, 50)));

    //Populate the Menus

    this->mainMenu.append("PROGRAMS");
    this->mainMenu.append("FREQUENCY");

    this->programsMenu.append("HEAD");
    this->programsMenu.append("JOINTS");
    this->programsMenu.append("NECK");

    this->frequencyMenu.append("10 Hz");
    this->frequencyMenu.append("60 Hz");
    this->frequencyMenu.append("125 Hz");
    this->frequencyMenu.append("200 Hz");


    //Add the menu Nodes to the Hash
    this->menuData.insert("MAIN",mainMenuNode);
    this->menuData.insert("PROGRAMS",programsMenuNode);
    this->menuData.insert("FREQUENCY",frequencyMenuNode);


    //Add the programs to the Hash
    this->programsData.insert("HEAD","Program");
    this->programsData.insert("JOINTS","Program");
    this->programsData.insert("NECK","Program");

    //Add the frequencies to the Hash
    this->frequencyData.insert("10 Hz","Program");
    this->frequencyData.insert("60 Hz","Program");
   this->frequencyData.insert("125 Hz","Program");
    this->frequencyData.insert("200 Hz","Program");


    //When the simulation starts, display the Main menu and select the top item
    displayMenu(&mainMenu);


    ui->programTitleLabel->setVisible(false);
    ui->pictureLabel->setVisible(false);
    ui->fillerLabel->setVisible(false);

}

MainWindow::~MainWindow()
{

    delete scene;
    delete powerBtn;
    delete ui;
}

void MainWindow::on_okButton_clicked()
{   /*
      * Okay button has many features and decides which to use depending
      * on what widgets are visible.
      * 1. If the Menu is visible it will select a menu Option
      * 2. If a body part image is visible it will display the power level bar
      * 3. If the power level bar is visible, it will display the Timer
      */

    //1. If the Menu is visible it will select a menu Option
    if(!ui->listWidget->isHidden()){

        //Get the text from the selected option.  If the text represents a Menu, go to that menu.
        // If the text represents a program, start that program
        selection = ui->listWidget->currentItem()->text();

        //1.1 Text represents a Menu
        if(this->menuData.contains(selection)){
            u = Node(this->menuData.value(selection));
            displayMenu(u.getData());

            //Store the Node's parent for the Back button
            u = u.getParent();
            previousMenuNode = &u;
        }


        //1.2 Text represents a Body Part Program
        else if(this->programsData.contains(selection)){
            ui->pictureLabel->setVisible(true);
            ui->fillerLabel->setVisible(true);

            ui->listWidget->setDisabled(true);
            ui->listWidget->setHidden(true);

            ui->programTitleLabel->setVisible(true);
            ui->programTitleLabel->setText(selection.toUpper());

            ui->pictureLabel->setPixmap(QPixmap(":/images/" + selection + ".png"));
        }

         //1.3 Text represents a Frequency program
        else if(this->frequencyData.contains(selection)){
            ui->powerLevelProgBar->setVisible(true);
            ui->fillerLabel->setVisible(true);

            ui->listWidget->setDisabled(true);
            ui->listWidget->setHidden(true);

            ui->programTitleLabel->setVisible(true);
            ui->programTitleLabel->setText(selection.toUpper());
        }
    }

//2. If a body part image is visible it will display the power level bar
    else if(ui->pictureLabel->isVisible()){
        ui->pictureLabel->setVisible(false);
        ui->powerLevelProgBar->setVisible(true);
    }
//3. If the power level bar is visible, it will display the Timer
    else if(ui->powerLevelProgBar->isVisible()){
        ui->powerLevelProgBar->setVisible(false);
        ui->timer->setVisible(true);
    }
}


void MainWindow::on_backButton_clicked()
{
    if(!ui->listWidget->isEnabled()){

        //Make everything not part of the main menu invisible
        ui->timer->setVisible(false);
        ui->pictureLabel->setVisible(false);
        ui->fillerLabel->setVisible(false);
        ui->powerLevelProgBar->setVisible(false);
        ui->programTitleLabel->setVisible(false);

        //Display the Main menu and select the top item
        ui->listWidget->setDisabled(false);
        ui->listWidget->setHidden(false);

    }
    else{
        displayMenu(previousMenuNode->getData());
    }
}

void MainWindow::on_upButton_clicked()
{
    if(ui->listWidget->currentRow() > 0){
        ui->listWidget->setCurrentRow(ui->listWidget->currentRow() - 1);
    }
    else{
        ui->listWidget->setCurrentRow(ui->listWidget->currentRow());
    }
}

void MainWindow::on_downButton_clicked()
{
    if(ui->listWidget->currentRow() < (ui->listWidget->count()-1)){
        ui->listWidget->setCurrentRow(ui->listWidget->currentRow() + 1);
    }
    else{
        ui->listWidget->setCurrentRow(ui->listWidget->currentRow());
    }
}

void MainWindow::displayMenu(QStringList *l){
    //Make everything not part of the main menu invisible
    ui->timer->setVisible(false);
    ui->pictureLabel->setVisible(false);
    ui->fillerLabel->setVisible(false);
    ui->powerLevelProgBar->setVisible(false);

    //Display the Main menu and select the top item
    ui->listWidget->setDisabled(false);
    ui->listWidget->setHidden(false);
    ui->listWidget->clear();
    ui->listWidget->addItems(*l);
    ui->listWidget->setCurrentRow(0);
}

void MainWindow::on_leftButton_clicked()
{
    updatePowerLevelProgBar("decrease");
}

void MainWindow::on_rightButton_clicked()
{
    updatePowerLevelProgBar("increase");

}

void MainWindow::updatePowerLevelProgBar(QString s){
    if(ui->listWidget->isHidden()){
        ui->pictureLabel->setVisible(false);
        ui->powerLevelProgBar->setVisible(true);

        if(s == "increase"){
            if(powerLevel < 100){
                powerLevel += 1;
            }

            ui->powerLevelProgBar->setValue(powerLevel);
        }
        else if(s== "decrease"){
            if(powerLevel > 0){
                powerLevel -= 1;
            }

            ui->powerLevelProgBar->setValue(powerLevel);
        }
    }
}
