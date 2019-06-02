#include "stdafx.h"
#include "ReturnButton.h"

ReturnButton::ReturnButton(QWidget *parent)
	: QPushButton(parent)
{
	initialStyle();
	connect(this, SIGNAL(clicked()), this, SLOT(returnClicked()));
}

ReturnButton::~ReturnButton()
{
}

void ReturnButton::initialStyle()
{
	/*auto font = QFont("Microsoft YaHei", 8, 50, true);
	setFont(font);
	setText("RETURN");
	setStyleSheet("color: black");
	setMaximumSize(70, 40);*/
}

void ReturnButton::returnClicked() 
{
	emit returnSignal();
}
