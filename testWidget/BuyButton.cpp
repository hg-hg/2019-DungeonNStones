#include "stdafx.h"
#include "BuyButton.h"

BuyButton::BuyButton(QWidget *parent)
	: QPushButton(parent)
{
	initialStyle();
	connect(this, SIGNAL(clicked()),this,SLOT(buyClicked()));
}

BuyButton::~BuyButton()
{
}

//this is the style of the BuyButton
void BuyButton::initialStyle()
{
	auto font = QFont("Microsoft YaHei", 8, 50, true);
	setFont(font);
	setText("BUY");
	setStyleSheet("color: black");
}

void BuyButton::buyClicked() 
{
	emit buySignal();
}