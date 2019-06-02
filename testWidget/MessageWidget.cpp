#include "stdafx.h"
#include "MessageWidget.h"

MessageWidget::MessageWidget(QWidget *parent,Character* character)
	: QWidget(parent)
{
	ui.setupUi(this);
	setCharacter(character);
	initialLabels();
	initialDisplay();
	initialReturnEvent();
}

MessageWidget::~MessageWidget()
{
}

void MessageWidget::setCharacter(Character * character)
{
	this->character = character;
}

ReturnButton * MessageWidget::getReturnButton()
{
	return ui.returnButton;
}

void MessageWidget::initialDisplay()
{
	ui.gridLayout->setVerticalSpacing(50);
	ui.gridLayout->setHorizontalSpacing(20);
	int i;
	for ( i = 0;i < labels.size();i++) 
	{
		ui.gridLayout->addWidget(labels[i].first,i, 0, 1, 1);
		ui.gridLayout->addWidget(labels[i].second, i, 1, 1, 1);
	}
	auto description = new QLabel("Description :");
	ui.gridLayout->addWidget(description,i,0,1,1);
	initialDescription();
}

void MessageWidget::initialReturnEvent()
{
	connect(ui.returnButton, SIGNAL(returnSignal()), this, SLOT(deleteThis()));
}

void MessageWidget::initialLabels()
{
	labels.clear();
	auto name = new QLabel("Name : "); auto nameCon = new QLabel(character->name);
	auto HP = new QLabel("HP : "); auto hpCon = new QLabel(QString::number(character->hp));
	auto MP = new QLabel("MP : "); auto mpCon = new QLabel(QString::number(character->mp));
	auto price = new QLabel("Price : "); auto priceCon = new QLabel(QString::number(character->price));
	labels.push_back(QPair<QLabel*,QLabel*>(name, nameCon));
	labels.push_back(QPair<QLabel*, QLabel*>(HP, hpCon));
	labels.push_back(QPair<QLabel*, QLabel*>(MP, mpCon));
	labels.push_back(QPair<QLabel*, QLabel*>(price, priceCon));
}

void MessageWidget::initialDescription()
{
	ui.descriptionField->append(character->description + "\n");
}



void MessageWidget::deleteThis() 
{
	emit deleteSignal();
}

