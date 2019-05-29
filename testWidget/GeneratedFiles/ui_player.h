/********************************************************************************
** Form generated from reading UI file 'player.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PLAYER_H
#define UI_PLAYER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_PlayerWidget
{
public:
    QProgressBar *HP;
    QProgressBar *MP;
    QLabel *characterInfo;
    QWidget *verticalLayoutWidget;
    QVBoxLayout *skills;

    void setupUi(QWidget *PlayerWidget)
    {
        if (PlayerWidget->objectName().isEmpty())
            PlayerWidget->setObjectName(QString::fromUtf8("PlayerWidget"));
        PlayerWidget->resize(271, 603);
        HP = new QProgressBar(PlayerWidget);
        HP->setObjectName(QString::fromUtf8("HP"));
        HP->setGeometry(QRect(50, 310, 141, 23));
        HP->setValue(100);
        MP = new QProgressBar(PlayerWidget);
        MP->setObjectName(QString::fromUtf8("MP"));
        MP->setGeometry(QRect(50, 360, 141, 23));
        MP->setValue(0);
        characterInfo = new QLabel(PlayerWidget);
        characterInfo->setObjectName(QString::fromUtf8("characterInfo"));
        characterInfo->setGeometry(QRect(60, 10, 131, 271));
        verticalLayoutWidget = new QWidget(PlayerWidget);
        verticalLayoutWidget->setObjectName(QString::fromUtf8("verticalLayoutWidget"));
        verticalLayoutWidget->setGeometry(QRect(50, 410, 141, 171));
        skills = new QVBoxLayout(verticalLayoutWidget);
        skills->setSpacing(2);
        skills->setObjectName(QString::fromUtf8("skills"));
        skills->setContentsMargins(0, 0, 0, 0);

        retranslateUi(PlayerWidget);

        QMetaObject::connectSlotsByName(PlayerWidget);
    } // setupUi

    void retranslateUi(QWidget *PlayerWidget)
    {
        PlayerWidget->setWindowTitle(QApplication::translate("PlayerWidget", "Form", nullptr));
        HP->setFormat(QApplication::translate("PlayerWidget", "%v", nullptr));
        MP->setFormat(QApplication::translate("PlayerWidget", "%v", nullptr));
        characterInfo->setText(QApplication::translate("PlayerWidget", "TextLabel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class PlayerWidget: public Ui_PlayerWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PLAYER_H
