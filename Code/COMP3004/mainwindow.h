#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QHash>
#include <QStringList>
#include "Node.h"
#include <iostream>
#include <QPixmap>
#include <QPushButton>
#include <QGraphicsScene>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void displayMenu(QStringList* l);
    void updatePowerLevelProgBar(QString s);

private slots:
    void on_okButton_clicked();

    void on_backButton_clicked();

    void on_upButton_clicked();

    void on_downButton_clicked();

    void on_leftButton_clicked();

    void on_rightButton_clicked();

private:
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    QPushButton *powerBtn;

    QStringList mainMenu;
    QStringList programsMenu;
    QStringList frequencyMenu;

    Node mainMenuNode;
    Node programsMenuNode;
    Node frequencyMenuNode;

    Node u; //placeholder

    Node* previousMenuNode = nullptr;

    int powerLevel = 0;

    QString selection;
    QHash<QString, Node > menuData;
    QHash<QString, QString > programsData;
    QHash<QString, QString > frequencyData;


};
#endif // MAINWINDOW_H
