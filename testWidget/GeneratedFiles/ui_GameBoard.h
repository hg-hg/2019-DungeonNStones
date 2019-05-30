/********************************************************************************
** Form generated from reading UI file 'GameBoard.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAMEBOARD_H
#define UI_GAMEBOARD_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QWidget>
#include <gamelogic.h>
#include <player.h>

QT_BEGIN_NAMESPACE

class Ui_GameBoard
{
public:
    Player *player;
    GameLogic *gameCore;
    Player *enemy;
    QLabel *backPic;
    QLabel *label;

    void setupUi(QWidget *GameBoard)
    {
        if (GameBoard->objectName().isEmpty())
            GameBoard->setObjectName(QString::fromUtf8("GameBoard"));
        GameBoard->resize(1112, 640);
        player = new Player(GameBoard);
        player->setObjectName(QString::fromUtf8("player"));
        player->setGeometry(QRect(1, 1, 300, 641));
        gameCore = new GameLogic(GameBoard);
        gameCore->setObjectName(QString::fromUtf8("gameCore"));
        gameCore->setGeometry(QRect(300, 50, 512, 512));
        gameCore->setMinimumSize(QSize(512, 512));
        enemy = new Player(GameBoard);
        enemy->setObjectName(QString::fromUtf8("enemy"));
        enemy->setGeometry(QRect(812, 1, 300, 641));
        backPic = new QLabel(GameBoard);
        backPic->setObjectName(QString::fromUtf8("backPic"));
        backPic->setGeometry(QRect(3, 1, 1111, 641));
        backPic->setPixmap(QPixmap(QString::fromUtf8("background/wall.png")));
        label = new QLabel(GameBoard);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(280, 30, 551, 551));
        label->setPixmap(QPixmap(QString::fromUtf8("background/wall_core.png")));
        label->setScaledContents(true);
        backPic->raise();
        player->raise();
        enemy->raise();
        label->raise();
        gameCore->raise();

        retranslateUi(GameBoard);

        QMetaObject::connectSlotsByName(GameBoard);
    } // setupUi

    void retranslateUi(QWidget *GameBoard)
    {
        GameBoard->setWindowTitle(QApplication::translate("GameBoard", "Form", nullptr));
        backPic->setText(QString());
        label->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class GameBoard: public Ui_GameBoard {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAMEBOARD_H
