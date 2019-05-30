/********************************************************************************
** Form generated from reading UI file 'GameServerWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMESERVERWINDOW_H
#define UI_GAMESERVERWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_GameServerWindowClass
{
public:
    QWidget *centralWidget;
    QLabel *label;
    QLabel *client;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *GameServerWindowClass)
    {
        if (GameServerWindowClass->objectName().isEmpty())
            GameServerWindowClass->setObjectName(QString::fromUtf8("GameServerWindowClass"));
        GameServerWindowClass->resize(828, 548);
        centralWidget = new QWidget(GameServerWindowClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        label = new QLabel(centralWidget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(100, 70, 541, 141));
        client = new QLabel(centralWidget);
        client->setObjectName(QString::fromUtf8("client"));
        client->setGeometry(QRect(90, 360, 601, 121));
        GameServerWindowClass->setCentralWidget(centralWidget);
        statusBar = new QStatusBar(GameServerWindowClass);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        GameServerWindowClass->setStatusBar(statusBar);

        retranslateUi(GameServerWindowClass);

        QMetaObject::connectSlotsByName(GameServerWindowClass);
    } // setupUi

    void retranslateUi(QMainWindow *GameServerWindowClass)
    {
        GameServerWindowClass->setWindowTitle(QApplication::translate("GameServerWindowClass", "GameServerWindow", nullptr));
        label->setText(QApplication::translate("GameServerWindowClass", "TextLabel", nullptr));
        client->setText(QApplication::translate("GameServerWindowClass", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class GameServerWindowClass: public Ui_GameServerWindowClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMESERVERWINDOW_H
