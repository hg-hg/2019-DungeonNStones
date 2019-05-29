/********************************************************************************
** Form generated from reading UI file 'PVE.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PVE_H
#define UI_PVE_H

#include <Gameboard.h>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PVE
{
public:
    QGridLayout *gridLayout;
    GameBoard *gameBoard;

    void setupUi(QWidget *PVE)
    {
        if (PVE->objectName().isEmpty())
            PVE->setObjectName(QString::fromUtf8("PVE"));
        PVE->resize(937, 0);
        gridLayout = new QGridLayout(PVE);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        gameBoard = new GameBoard(PVE);
        gameBoard->setObjectName(QString::fromUtf8("gameBoard"));

        gridLayout->addWidget(gameBoard, 0, 0, 1, 1);


        retranslateUi(PVE);

        QMetaObject::connectSlotsByName(PVE);
    } // setupUi

    void retranslateUi(QWidget *PVE)
    {
        PVE->setWindowTitle(QApplication::translate("PVE", "PVE", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PVE: public Ui_PVE {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PVE_H
