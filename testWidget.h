#pragma once

#include <QtWidgets/QMainWindow>
#include "GameBoard.h"
#include "ui_testWidget.h"

class testWidget : public QMainWindow
{
	Q_OBJECT

public:
	testWidget(QWidget *parent = Q_NULLPTR);

protected:
	
private:
	Ui::testWidgetClass ui;

};
