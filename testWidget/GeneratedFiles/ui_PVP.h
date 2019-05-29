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
    QLabel *label;
    GameBoard *playing;

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
        label = new QLabel(waiting);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(270, 260, 331, 241));
        QFont font;
        font.setFamily(QString::fromUtf8("Adobe Arabic"));
        font.setPointSize(48);
        label->setFont(font);
        stack->addWidget(waiting);
        playing = new GameBoard();
        playing->setObjectName(QString::fromUtf8("playing"));
        stack->addWidget(playing);

        gridLayout->addWidget(stack, 0, 0, 1, 1);


        retranslateUi(PVP);

        QMetaObject::connectSlotsByName(PVP);
    } // setupUi

    void retranslateUi(QWidget *PVP)
    {
        PVP->setWindowTitle(QApplication::translate("PVP", "PVP", nullptr));
        label->setText(QApplication::translate("PVP", "\347\255\211\345\276\205\345\214\271\351\205\215", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PVP: public Ui_PVP {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PVP_H
