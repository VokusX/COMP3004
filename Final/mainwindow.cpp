#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "QGraphicsScene"
#include <QTimer>
#include <QTime>
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
    powerBtn->setStyleSheet("QPushButton{background: transparent;}");
    connect(powerBtn, SIGNAL (released()),this, SLOT (on_powerButton_clicked()));

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

    // hide all the UI elements until we power on
    ui->batteryLabel->hide();
    ui->fillerLabel->hide();
    ui->programTitleLabel->hide();
    ui->listWidget->hide();
    ui->powerLevelLabel->hide();
    ui->powerLevelProgBar->hide();
    ui->batteryProgBar->hide();
    ui->timer->hide();

    // disable all the buttons until needed
    ui->okButton->hide();
    ui->upButton->hide();
    ui->downButton->hide();
    ui->rightButton->hide();
    ui->leftButton->hide();
    ui->backButton->hide();

    // set button backrounds to transparent
    ui->okButton->setStyleSheet("QPushButton{background: transparent;}");
    ui->upButton->setStyleSheet("QPushButton{background: transparent;}");
    ui->downButton->setStyleSheet("QPushButton{background: transparent;}");
    ui->rightButton->setStyleSheet("QPushButton{background: transparent;}");
    ui->leftButton->setStyleSheet("QPushButton{background: transparent;}");
    ui->backButton->setStyleSheet("QPushButton{background: transparent;}");

}

MainWindow::~MainWindow()
{

    delete scene;
    delete powerBtn;
    delete ui;
}

void MainWindow::on_powerButton_clicked() {
    // two cases, either we are powering on or powering off and toggle the power state
    if(powerOn){
        // hide all the UI elements until we power on
        ui->batteryLabel->hide();
        ui->fillerLabel->hide();
        ui->programTitleLabel->hide();
        ui->listWidget->hide();
        ui->powerLevelLabel->hide();
        ui->batteryProgBar->hide();
        ui->pictureLabel->hide();
        ui->program_lbl->hide();
        ui->program_freq->hide();
        ui->program_wave->hide();

        // disable all the buttons until needed
        ui->okButton->hide();
        ui->upButton->hide();
        ui->downButton->hide();
        ui->rightButton->hide();
        ui->leftButton->hide();
        ui->backButton->hide();
    }
    // otherwise power on the device
    else{
        // init all the central proccess functions
        cp.initialize();

        //When the simulation starts, display the Main menu and select the top item
        displayMenu(&mainMenu);
        std::string ba = std::to_string(cp.batteryLevel) + "%";
        QString qstr = QString::fromStdString(ba);

        ui->batteryProgBar->setValue(cp.batteryLevel);

        ui->batteryLabel->setText(qstr);
        ui->programTitleLabel->setVisible(false);
        ui->pictureLabel->setVisible(false);
        ui->fillerLabel->setVisible(false);


        ui->program_lbl->setVisible(false);
        ui->program_freq->setVisible(false);
        ui->program_wave->setVisible(false);

        ui->program_lbl->setText("");
        ui->program_freq->setText("");
        ui->program_wave->setText("");

        ba = std::to_string(cp.powerLevel) + " power level";
        qstr = QString::fromStdString(ba);

        ui->powerLevelLabel->setText(qstr);

        // Set up Timer
        t = new QTimer(this);
        t->setInterval(1000);
        connect(t, &QTimer::timeout, [&]() {
            cp.timeOfTherapy += 1;
            updateTimer();
            updateBattery();
            updateLabels();
            cp.runSim();
            cp.checkBatteryLevel();

            if(cp.batteryLevel < 1) {
                t->stop();
            }

            //cp.runSim();


           //ui->timer->setText(time1);
        } );

        updateBattery();

        // re-enable buttons and display menu
        // hide all the UI elements until we power on
        ui->batteryLabel->show();
        ui->listWidget->show();
        ui->powerLevelLabel->show();
        ui->batteryProgBar->show();

        // disable all the buttons until needed
        ui->okButton->show();
        ui->upButton->show();
        ui->downButton->show();
        ui->rightButton->show();
        ui->leftButton->show();
        ui->backButton->show();
    }

    // toggle the power state
    powerOn = !powerOn;
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

            Program p;
            if(selection.toStdString() == "HEAD") {
            // This is to let the case handling that a head pain has just been selected.
                p.name = "Head Pain";
                p.freq = 68;
                p.waveform = "Sinusoidal";

            } else if (selection.toStdString() == "JOINTS") {
            // This is to let the case handling that a joint pain has just been selected.
                p.name = "Joint Pain";
                p.freq = 250;
                p.waveform = "Sinusoidal";

            } else if (selection.toStdString() == "NECK") {
            // This is to let the case handling that a neck pain has just been selected.
                p.name = "Neck Pain";
                p.freq = 77;
                p.waveform = "Sinusoidal";
            }

            cp.program = p;

        }

         //1.3 Text represents a Frequency program
        else if(this->frequencyData.contains(selection)){
            ui->powerLevelProgBar->setVisible(true);
            ui->fillerLabel->setVisible(true);

            ui->listWidget->setDisabled(true);
            ui->listWidget->setHidden(true);

            ui->programTitleLabel->setVisible(true);
            ui->programTitleLabel->setText(selection.toUpper());

            Program p;
            if(selection.toStdString() == "10 Hz") {
            // This is to let the case handling that 10hz has just been selected.
                p.name = "10 Hz";
                p.freq = 10;
                p.waveform = "Sinusoidal";

            } else if (selection.toStdString() == "60 Hz") {
            // This is to let the case handling that 60hz has just been selected.
                p.name = "60 Hz";
                p.freq = 60;
                p.waveform = "Sinusoidal";

            } else if (selection.toStdString() == "125 Hz") {
            // This is to let the case handling that 125hz has just been selected.
                p.name = "125 Hz";
                p.freq = 125;
                p.waveform = "Sinusoidal";

            } else if (selection.toStdString() == "200 Hz") {
            // This is to let the case handling that 200hz has just been selected.
                p.name = "200 Hz";
                p.freq = 200;
                p.waveform = "Sinusoidal";
            }

            cp.program = p;

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
        ui->program_lbl->setVisible(true);
        ui->program_freq->setVisible(true);
        ui->program_wave->setVisible(true);
        t->start();
    }

    else if(ui->timer->isVisible()){
        ui->powerLevelProgBar->setVisible(false);
        ui->program_lbl->setVisible(false);
        ui->program_freq->setVisible(false);
        ui->program_wave->setVisible(false);
        t->stop();

        ui->program_lbl->setText("Program Ended.");
        updateLabels();
    }
}


void MainWindow::on_backButton_clicked()
{
    updatePowerLevelProgBar("");
    if(ui->timer->isVisible()){
        t->stop();
        ui->program_lbl->setVisible(false);
        ui->program_freq->setVisible(false);
        ui->program_wave->setVisible(false);
        cp.reset();

    }

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
            if(cp.powerLevel < 100){
                cp.powerLevel += 5;
            }

            ui->powerLevelProgBar->setValue(cp.powerLevel);
        }
        else if(s== "decrease"){
            if(cp.powerLevel > 0){
                cp.powerLevel -= 5;
            }

            ui->powerLevelProgBar->setValue(cp.powerLevel);
        }
    }
    std::string ba = std::to_string(cp.powerLevel) + " power level";
    QString qstr = QString::fromStdString(ba);
    ui->powerLevelLabel->setText(qstr);
}

void MainWindow::updateTimer(){
    //std::string ba = std::to_string(cp.batteryLevel) + "%";
    int divider = cp.timeOfTherapy/60;
    int remainder = cp.timeOfTherapy - (divider*60);


    std::string remainder_str;
    if(remainder < 10) {
        remainder_str = "0" + std::to_string(remainder);
    } else {
        remainder_str = std::to_string(remainder);
    }
    std::string str = std::to_string(divider) + ":" + remainder_str;
;
    QString qstr = QString::fromStdString(str);
    ui->timer->setText(qstr);
}

void MainWindow::updateBattery() {
    std::string ba = std::to_string(cp.batteryLevel) + "%";
    QString qstr = QString::fromStdString(ba);

    ui->batteryProgBar->setValue(cp.batteryLevel);

    ui->batteryLabel->setText(qstr);
}

void MainWindow::updateLabels() {

    QString p_name = "Program: " + QString::fromStdString(cp.program.name);
    QString p_freq = "Frequency: " + QString::fromStdString(std::to_string(cp.program.freq)) + "hz";
    QString p_wave = "Waveform: " + QString::fromStdString(cp.program.waveform);

    ui->program_lbl->setText(p_name);
    ui->program_freq->setText(p_freq);
    ui->program_wave->setText(p_wave);
}
