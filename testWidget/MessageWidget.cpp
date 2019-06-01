#include "stdafx.h"
#include "MessageWidget.h"

MessageWidget::MessageWidget(QWidget *parent, Character * character)
	: QWidget(parent)
{
	setCharacter(character);
	initialDisplay();
	initialReturnButton();
	initialLayout();
	initialReturnEvent();
}

MessageWidget::~MessageWidget()
{
}

QSize MessageWidget::sizeHint() const
{
	return originSize;
}

ReturnButton * MessageWidget::getReturnButton()
{
	return returnButton;
}

void MessageWidget::setCharacter(Character * character)
{
	this->character = character;
}

void MessageWidget::initialLayout()
{
	auto layout = new QGridLayout;
	layout->setVerticalSpacing(100);
	layout->setRowMinimumHeight(0, 400);
	layout->addWidget(displayFlied, 0, 0, 1, 3);
	layout->addWidget(returnButton, 1, 0, 1, 1);
	this->setLayout(layout);

}

void MessageWidget::initialDisplay()
{
	displayFlied = new QTextBrowser();
	auto font = QFont("Microsoft YaHei", 8, 50, true);
	displayFlied->setFont(font);
	displayFlied->append("Name : " + character->name + "\n");
	displayFlied->append("HP : " + QString::number(character->hp) + "\n");
	displayFlied->append("MP : " + QString::number(character->mp) + "\n");
	displayFlied->append("Price : " + QString::number(character->price) + "\n");
	displayFlied->append("Discription : " + character->description + "\n");

}

void MessageWidget::initialReturnEvent()
{
	connect(returnButton, SIGNAL(returnSignal()),this, SLOT(deleteThis()));
}

void MessageWidget::initialReturnButton()
{
	returnButton = new ReturnButton(this);
}

void MessageWidget::deleteThis() 
{
	emit deleteSignal();
}
