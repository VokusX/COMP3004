/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGraphicsView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *okButton;
    QListWidget *listWidget;
    QPushButton *backButton;
    QPushButton *upButton;
    QPushButton *downButton;
    QLabel *programTitleLabel;
    QLabel *batteryLabel;
    QProgressBar *batteryProgBar;
    QLabel *pictureLabel;
    QLabel *powerLevelLabel;
    QLabel *bottomLabel;
    QLabel *fillerLabel;
    QPushButton *leftButton;
    QPushButton *rightButton;
    QProgressBar *powerLevelProgBar;
    QLabel *timer;
    QGraphicsView *graphicsView;
    QMenuBar *menubar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(300, 775);
        MainWindow->setMinimumSize(QSize(300, 775));
        MainWindow->setMaximumSize(QSize(300, 775));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        okButton = new QPushButton(centralwidget);
        okButton->setObjectName(QString::fromUtf8("okButton"));
        okButton->setGeometry(QRect(130, 485, 50, 50));
        listWidget = new QListWidget(centralwidget);
        listWidget->setObjectName(QString::fromUtf8("listWidget"));
        listWidget->setGeometry(QRect(60, 160, 180, 167));
        backButton = new QPushButton(centralwidget);
        backButton->setObjectName(QString::fromUtf8("backButton"));
        backButton->setGeometry(QRect(65, 365, 50, 50));
        upButton = new QPushButton(centralwidget);
        upButton->setObjectName(QString::fromUtf8("upButton"));
        upButton->setGeometry(QRect(130, 420, 50, 50));
        downButton = new QPushButton(centralwidget);
        downButton->setObjectName(QString::fromUtf8("downButton"));
        downButton->setGeometry(QRect(130, 550, 50, 50));
        programTitleLabel = new QLabel(centralwidget);
        programTitleLabel->setObjectName(QString::fromUtf8("programTitleLabel"));
        programTitleLabel->setGeometry(QRect(60, 160, 180, 20));
        QFont font;
        font.setFamily(QString::fromUtf8("MS Sans Serif"));
        font.setBold(true);
        font.setWeight(75);
        programTitleLabel->setFont(font);
        programTitleLabel->setAutoFillBackground(false);
        programTitleLabel->setStyleSheet(QString::fromUtf8("background: rgb(0, 85, 127);\n"
"color: rgb(255, 255, 255);\n"
""));
        programTitleLabel->setAlignment(Qt::AlignCenter);
        batteryLabel = new QLabel(centralwidget);
        batteryLabel->setObjectName(QString::fromUtf8("batteryLabel"));
        batteryLabel->setGeometry(QRect(60, 140, 180, 20));
        batteryLabel->setStyleSheet(QString::fromUtf8("background:rgb(175, 211, 255);\n"
"color: white;\n"
"border-right-style: solid;\n"
"border-right-width: 1px;\n"
"border-top-style: solid;\n"
"border-top-width: 1px;\n"
"border-left-style: solid;\n"
"border-left-width: 1px;"));
        batteryLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        batteryProgBar = new QProgressBar(centralwidget);
        batteryProgBar->setObjectName(QString::fromUtf8("batteryProgBar"));
        batteryProgBar->setGeometry(QRect(180, 142, 12, 16));
        batteryProgBar->setValue(24);
        batteryProgBar->setTextVisible(false);
        batteryProgBar->setOrientation(Qt::Vertical);
        pictureLabel = new QLabel(centralwidget);
        pictureLabel->setObjectName(QString::fromUtf8("pictureLabel"));
        pictureLabel->setGeometry(QRect(99, 181, 107, 129));
        pictureLabel->setTextFormat(Qt::AutoText);
        pictureLabel->setScaledContents(true);
        pictureLabel->setAlignment(Qt::AlignCenter);
        powerLevelLabel = new QLabel(centralwidget);
        powerLevelLabel->setObjectName(QString::fromUtf8("powerLevelLabel"));
        powerLevelLabel->setGeometry(QRect(60, 310, 61, 20));
        powerLevelLabel->setStyleSheet(QString::fromUtf8("background:rgb(175, 211, 255);\n"
"color: white;\n"
"border-right-style: solid;\n"
"border-right-width: 1px;\n"
"border-bottom-style: solid;\n"
"border-bottom-width: 1px;\n"
"border-left-style: solid;\n"
"border-left-width: 1px;"));
        powerLevelLabel->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        bottomLabel = new QLabel(centralwidget);
        bottomLabel->setObjectName(QString::fromUtf8("bottomLabel"));
        bottomLabel->setGeometry(QRect(120, 310, 120, 20));
        bottomLabel->setStyleSheet(QString::fromUtf8("background:rgb(175, 211, 255);\n"
"color: white;\n"
"border-right-style: solid;\n"
"border-right-width: 1px;\n"
"border-bottom-style: solid;\n"
"border-bottom-width: 1px;\n"
""));
        fillerLabel = new QLabel(centralwidget);
        fillerLabel->setObjectName(QString::fromUtf8("fillerLabel"));
        fillerLabel->setGeometry(QRect(60, 180, 180, 130));
        fillerLabel->setAutoFillBackground(false);
        fillerLabel->setStyleSheet(QString::fromUtf8("background: white;\n"
"border-left-style: solid;\n"
"border-left-width: 1px;\n"
"border-right-style: solid;\n"
"border-right-width: 1px;"));
        leftButton = new QPushButton(centralwidget);
        leftButton->setObjectName(QString::fromUtf8("leftButton"));
        leftButton->setGeometry(QRect(65, 485, 50, 50));
        rightButton = new QPushButton(centralwidget);
        rightButton->setObjectName(QString::fromUtf8("rightButton"));
        rightButton->setGeometry(QRect(195, 485, 50, 50));
        powerLevelProgBar = new QProgressBar(centralwidget);
        powerLevelProgBar->setObjectName(QString::fromUtf8("powerLevelProgBar"));
        powerLevelProgBar->setGeometry(QRect(90, 232, 120, 21));
        powerLevelProgBar->setValue(24);
        timer = new QLabel(centralwidget);
        timer->setObjectName(QString::fromUtf8("timer"));
        timer->setGeometry(QRect(70, 210, 161, 61));
        QFont font1;
        font1.setFamily(QString::fromUtf8("MS Sans Serif"));
        font1.setPointSize(30);
        timer->setFont(font1);
        timer->setStyleSheet(QString::fromUtf8("font-size:30pt"));
        timer->setAlignment(Qt::AlignCenter);
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setGeometry(QRect(0, 0, 300, 775));
        graphicsView->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignTop);
        MainWindow->setCentralWidget(centralwidget);
        graphicsView->raise();
        listWidget->raise();
        fillerLabel->raise();
        okButton->raise();
        backButton->raise();
        upButton->raise();
        downButton->raise();
        batteryLabel->raise();
        batteryProgBar->raise();
        pictureLabel->raise();
        powerLevelLabel->raise();
        bottomLabel->raise();
        leftButton->raise();
        rightButton->raise();
        powerLevelProgBar->raise();
        timer->raise();
        programTitleLabel->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 300, 22));
        MainWindow->setMenuBar(menubar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        okButton->setText(QString());
        backButton->setText(QString());
        upButton->setText(QString());
        downButton->setText(QString());
        programTitleLabel->setText(QCoreApplication::translate("MainWindow", "<html><head/><body><p>PROGRAM TITLE</p></body></html>", nullptr));
        batteryLabel->setText(QCoreApplication::translate("MainWindow", "XXX %", nullptr));
        powerLevelLabel->setText(QCoreApplication::translate("MainWindow", "###", nullptr));
        bottomLabel->setText(QString());
        fillerLabel->setText(QString());
        leftButton->setText(QString());
        rightButton->setText(QString());
        powerLevelProgBar->setFormat(QCoreApplication::translate("MainWindow", "%p", nullptr));
        timer->setText(QCoreApplication::translate("MainWindow", "0:00", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
