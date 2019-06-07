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
	this->character->setData(character);
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
	const auto description = new QLabel("Description :", this);
	description->setStyleSheet("color : white");
	ui.gridLayout->addWidget(description, i, 0, 1, 1);
	initialDescription();

	const auto skinPath = ":/skin/Resources/skin/" + character->skin;
	
	if (skinPath.endsWith(".gif"))
	{
		auto skin = new QMovie(this);
		skin->setFileName(skinPath);

		auto skinSize = QSize(130, 200);
		auto he = skinSize.height();
		auto wi = skinSize.width();
		if (wi > ui.character->size().width())
		{
			he *= ui.character->size().width();
			he /= wi;
			wi = ui.character->size().width();
		}
		if (he > ui.character->size().height())
		{
			wi *= ui.character->size().height();
			wi /= he;
			he = ui.character->size().height();
		}
		ui.character->setMovie(skin);
		skin->start();
	} else
	{
		ui.character->setPixmap(QPixmap(skinPath));
	}
	
}

void MessageWidget::initialReturnEvent()
{
	connect(ui.returnButton, SIGNAL(clicked()), this, SLOT(deleteThis()));
}

void MessageWidget::initialLabels()
{
	labels.clear();
	const auto name = new QLabel("Name : ", ui.gridLayoutWidget);
	const auto nameContent = new QLabel(character->name, ui.gridLayoutWidget);
	const auto hp = new QLabel("HP : ", ui.gridLayoutWidget);
	const auto hpContent = new QLabel(QString::number(character->hp), ui.gridLayoutWidget);
	const auto mp = new QLabel("MP : ", ui.gridLayoutWidget);
	const auto mpContent = new QLabel(QString::number(character->mp), ui.gridLayoutWidget);
	const auto price = new QLabel("Price : ", ui.gridLayoutWidget);
	const auto priceContent = new QLabel(QString::number(character->price), ui.gridLayoutWidget);
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
	QTimer::singleShot(500, this, [=]() {
		emit deleteSignal();
	});
}
