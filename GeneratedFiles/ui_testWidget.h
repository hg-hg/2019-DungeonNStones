/********************************************************************************
** Form generated from reading UI file 'testWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTWIDGET_H
#define UI_TESTWIDGET_H

#include <GameBoard.h>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_testWidgetClass
{
public:
    QWidget *centralWidget;
    GameBoard *gb;
    QPushButton *resetGB;
    QPushButton *deleteStone;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QWidget *player;
    QWidget *enemy;

    void setupUi(QMainWindow *testWidgetClass)
    {
        if (testWidgetClass->objectName().isEmpty())
            testWidgetClass->setObjectName(QString::fromUtf8("testWidgetClass"));
        testWidgetClass->resize(900, 500);
        centralWidget = new QWidget(testWidgetClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gb = new GameBoard(centralWidget);
        gb->setObjectName(QString::fromUtf8("gb"));
        gb->setGeometry(QRect(209, 11, 482, 478));
        resetGB = new QPushButton(gb);
        resetGB->setObjectName(QString::fromUtf8("resetGB"));
        resetGB->setGeometry(QRect(250, 450, 93, 28));
        deleteStone = new QPushButton(gb);
        deleteStone->setObjectName(QString::fromUtf8("deleteStone"));
        deleteStone->setGeometry(QRect(360, 450, 93, 28));
        pushButton = new QPushButton(gb);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(140, 450, 93, 28));
        pushButton_2 = new QPushButton(gb);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(30, 450, 93, 28));
        player = new QWidget(centralWidget);
        player->setObjectName(QString::fromUtf8("player"));
        player->setGeometry(QRect(11, 11, 192, 478));
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(player->sizePolicy().hasHeightForWidth());
        player->setSizePolicy(sizePolicy);
        enemy = new QWidget(centralWidget);
        enemy->setObjectName(QString::fromUtf8("enemy"));
        enemy->setGeometry(QRect(697, 11, 192, 478));
        sizePolicy.setHeightForWidth(enemy->sizePolicy().hasHeightForWidth());
        enemy->setSizePolicy(sizePolicy);
        testWidgetClass->setCentralWidget(centralWidget);

        retranslateUi(testWidgetClass);
        QObject::connect(resetGB, SIGNAL(clicked()), gb, SLOT(fillBoard()));
        QObject::connect(deleteStone, SIGNAL(clicked()), gb, SLOT(deleteStone()));
        QObject::connect(pushButton, SIGNAL(clicked()), gb, SLOT(deleteRect()));
        QObject::connect(pushButton_2, SIGNAL(clicked()), gb, SLOT(forceExchange()));

        QMetaObject::connectSlotsByName(testWidgetClass);
    } // setupUi

    void retranslateUi(QMainWindow *testWidgetClass)
    {
        testWidgetClass->setWindowTitle(QApplication::translate("testWidgetClass", "testWidget", nullptr));
        resetGB->setText(QApplication::translate("testWidgetClass", "reset", nullptr));
        deleteStone->setText(QApplication::translate("testWidgetClass", "delete", nullptr));
        pushButton->setText(QApplication::translate("testWidgetClass", "rect", nullptr));
        pushButton_2->setText(QApplication::translate("testWidgetClass", "exchange", nullptr));
    } // retranslateUi

};

namespace Ui {
    class testWidgetClass: public Ui_testWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTWIDGET_H
