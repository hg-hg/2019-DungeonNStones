/********************************************************************************
** Form generated from reading UI file 'PVP.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PVP_H
#define UI_PVP_H

#include <Gameboard.h>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PVP
{
public:
    QGridLayout *gridLayout;
    QStackedWidget *stack;
    QWidget *waiting;
    QLabel *waitingForGame;
    GameBoard *playing;
    QWidget *disconnect;
    QLabel *enemyDisconnect;

    void setupUi(QWidget *PVP)
    {
        if (PVP->objectName().isEmpty())
            PVP->setObjectName(QString::fromUtf8("PVP"));
        PVP->resize(936, 754);
        gridLayout = new QGridLayout(PVP);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        stack = new QStackedWidget(PVP);
        stack->setObjectName(QString::fromUtf8("stack"));
        waiting = new QWidget();
        waiting->setObjectName(QString::fromUtf8("waiting"));
        waitingForGame = new QLabel(waiting);
        waitingForGame->setObjectName(QString::fromUtf8("waitingForGame"));
        waitingForGame->setGeometry(QRect(270, 260, 331, 241));
        QFont font;
        font.setFamily(QString::fromUtf8("Adobe Arabic"));
        font.setPointSize(48);
        waitingForGame->setFont(font);
        stack->addWidget(waiting);
        playing = new GameBoard();
        playing->setObjectName(QString::fromUtf8("playing"));
        stack->addWidget(playing);
        disconnect = new QWidget();
        disconnect->setObjectName(QString::fromUtf8("disconnect"));
        enemyDisconnect = new QLabel(disconnect);
        enemyDisconnect->setObjectName(QString::fromUtf8("enemyDisconnect"));
        enemyDisconnect->setGeometry(QRect(130, 270, 701, 271));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Adobe Arabic"));
        font1.setPointSize(72);
        enemyDisconnect->setFont(font1);
        stack->addWidget(disconnect);

        gridLayout->addWidget(stack, 0, 0, 1, 1);


        retranslateUi(PVP);

        stack->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(PVP);
    } // setupUi

    void retranslateUi(QWidget *PVP)
    {
        PVP->setWindowTitle(QApplication::translate("PVP", "PVP", nullptr));
        waitingForGame->setText(QApplication::translate("PVP", "\347\255\211\345\276\205\345\214\271\351\205\215", nullptr));
        enemyDisconnect->setText(QApplication::translate("PVP", "\346\225\214\344\272\272\351\200\203\350\267\221\344\272\206", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PVP: public Ui_PVP {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PVP_H
