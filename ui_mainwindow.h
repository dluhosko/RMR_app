/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QStatusBar>
#include <QtGui/QTextEdit>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QPushButton *pushButton;
    QLabel *label;
    QPushButton *pushButton_2;
    QTextEdit *onX;
    QPushButton *pointButton;
    QPushButton *turnButton;
    QTextEdit *onY;
    QTextEdit *turnDegrees;
    QLabel *label2;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label2_2;
    QLabel *label2_3;
    QTextEdit *textEdit;
    QLabel *label2_4;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(546, 405);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        pushButton = new QPushButton(centralWidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(10, 10, 61, 51));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(70, 30, 251, 21));
        pushButton_2 = new QPushButton(centralWidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(10, 70, 61, 51));
        onX = new QTextEdit(centralWidget);
        onX->setObjectName(QString::fromUtf8("onX"));
        onX->setGeometry(QRect(100, 150, 101, 21));
        pointButton = new QPushButton(centralWidget);
        pointButton->setObjectName(QString::fromUtf8("pointButton"));
        pointButton->setGeometry(QRect(10, 130, 81, 51));
        turnButton = new QPushButton(centralWidget);
        turnButton->setObjectName(QString::fromUtf8("turnButton"));
        turnButton->setGeometry(QRect(360, 20, 101, 31));
        onY = new QTextEdit(centralWidget);
        onY->setObjectName(QString::fromUtf8("onY"));
        onY->setGeometry(QRect(100, 190, 101, 21));
        turnDegrees = new QTextEdit(centralWidget);
        turnDegrees->setObjectName(QString::fromUtf8("turnDegrees"));
        turnDegrees->setGeometry(QRect(100, 230, 101, 21));
        label2 = new QLabel(centralWidget);
        label2->setObjectName(QString::fromUtf8("label2"));
        label2->setGeometry(QRect(80, 90, 281, 21));
        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(90, 10, 211, 21));
        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(80, 60, 211, 21));
        label2_2 = new QLabel(centralWidget);
        label2_2->setObjectName(QString::fromUtf8("label2_2"));
        label2_2->setGeometry(QRect(100, 130, 211, 21));
        label2_3 = new QLabel(centralWidget);
        label2_3->setObjectName(QString::fromUtf8("label2_3"));
        label2_3->setGeometry(QRect(120, 210, 211, 21));
        textEdit = new QTextEdit(centralWidget);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setGeometry(QRect(270, 60, 271, 281));
        label2_4 = new QLabel(centralWidget);
        label2_4->setObjectName(QString::fromUtf8("label2_4"));
        label2_4->setGeometry(QRect(100, 170, 211, 21));
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 546, 27));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("MainWindow", "connect", 0, QApplication::UnicodeUTF8));
        label->setText(QString());
        pushButton_2->setText(QApplication::translate("MainWindow", "move", 0, QApplication::UnicodeUTF8));
        onX->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Roboto'; font-size:12pt; font-weight:200; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", 0, QApplication::UnicodeUTF8));
        pointButton->setText(QApplication::translate("MainWindow", "ON POINT", 0, QApplication::UnicodeUTF8));
        turnButton->setText(QApplication::translate("MainWindow", "Read Laser", 0, QApplication::UnicodeUTF8));
        onY->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Roboto'; font-size:12pt; font-weight:200; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", 0, QApplication::UnicodeUTF8));
        turnDegrees->setHtml(QApplication::translate("MainWindow", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Roboto'; font-size:12pt; font-weight:200; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">0</p></body></html>", 0, QApplication::UnicodeUTF8));
        label2->setText(QString());
        label_2->setText(QApplication::translate("MainWindow", "Desired position", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Actual position", 0, QApplication::UnicodeUTF8));
        label2_2->setText(QApplication::translate("MainWindow", "     X ", 0, QApplication::UnicodeUTF8));
        label2_3->setText(QApplication::translate("MainWindow", "fi", 0, QApplication::UnicodeUTF8));
        label2_4->setText(QApplication::translate("MainWindow", "     Y", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
