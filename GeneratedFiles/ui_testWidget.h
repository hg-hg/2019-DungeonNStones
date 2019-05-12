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
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_testWidgetClass
{
public:
    QWidget *centralWidget;
    GameBoard *gb;
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

        QMetaObject::connectSlotsByName(testWidgetClass);
    } // setupUi

    void retranslateUi(QMainWindow *testWidgetClass)
    {
        testWidgetClass->setWindowTitle(QApplication::translate("testWidgetClass", "testWidget", nullptr));
    } // retranslateUi

};

namespace Ui {
    class testWidgetClass: public Ui_testWidgetClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTWIDGET_H
