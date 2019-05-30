/********************************************************************************
** Form generated from reading UI file 'testWidget.ui'
**
** Created by: Qt User Interface Compiler version 5.12.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTWIDGET_H
#define UI_TESTWIDGET_H

#include <PVP.h>
#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_testWidgetClass
{
public:
    QWidget *centralWidget;
    PVP *gb;

    void setupUi(QMainWindow *testWidgetClass)
    {
        if (testWidgetClass->objectName().isEmpty())
            testWidgetClass->setObjectName(QString::fromUtf8("testWidgetClass"));
        testWidgetClass->resize(1292, 835);
        centralWidget = new QWidget(testWidgetClass);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gb = new PVP(centralWidget);
        gb->setObjectName(QString::fromUtf8("gb"));
        gb->setGeometry(QRect(30, 30, 1161, 791));
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
