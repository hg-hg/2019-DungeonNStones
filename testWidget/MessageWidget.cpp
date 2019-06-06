#include "stdafx.h"
#include "MessageWidget.h"

MessageWidget::MessageWidget(QWidget* parent, Character* character)
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

void MessageWidget::setCharacter(Character* character)
{
	this->character = character;
}

ReturnButton* MessageWidget::getReturnButton()
{
	return ui.returnButton;
}

void MessageWidget::initialDisplay()
{
	ui.gridLayout->setVerticalSpacing(50);
	ui.gridLayout->setHorizontalSpacing(20);
	int i;
	for (i = 0; i < labels.size(); i++)
	{
		labels[i].first->setStyleSheet("color : white");
		labels[i].second->setStyleSheet("color : white");
		ui.gridLayout->addWidget(labels[i].first, i, 0, 1, 1);
		ui.gridLayout->addWidget(labels[i].second, i, 1, 1, 1);
	}
	const auto description = new QLabel("Description :");
	description->setStyleSheet("color : white");
	ui.gridLayout->addWidget(description, i, 0, 1, 1);
	initialDescription();
}

void MessageWidget::initialReturnEvent()
{
	connect(ui.returnButton, SIGNAL(returnSignal()), this, SLOT(deleteThis()));
}

void MessageWidget::initialLabels()
{
	labels.clear();
	const auto name = new QLabel("Name : ");
	const auto nameContent = new QLabel(character->name);
	const auto hp = new QLabel("HP : ");
	const auto hpContent = new QLabel(QString::number(character->hp));
	const auto mp = new QLabel("MP : ");
	const auto mpContent = new QLabel(QString::number(character->mp));
	const auto price = new QLabel("Price : ");
	const auto priceContent = new QLabel(QString::number(character->price));
	labels.push_back(QPair<QLabel*, QLabel*>(name, nameContent));
	labels.push_back(QPair<QLabel*, QLabel*>(hp, hpContent));
	labels.push_back(QPair<QLabel*, QLabel*>(mp, mpContent));
	labels.push_back(QPair<QLabel*, QLabel*>(price, priceContent));
}

void MessageWidget::initialDescription()
{
	ui.descriptionField->append(character->description + "\n");
}


void MessageWidget::deleteThis()
{
	emit deleteSignal();
}
