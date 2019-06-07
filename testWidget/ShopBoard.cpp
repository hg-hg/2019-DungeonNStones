#include "stdafx.h"
#include "ShopBoard.h"
#include "ReturnButton.h"
#include <QTimer>


ShopBoard::ShopBoard(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initialVectors();
	initialMainWidget();
	initialStackWidget();
	initialSelectedCharacter();
	initialMoney();
}

ShopBoard::~ShopBoard()
{
}

void ShopBoard::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.fillRect(rect(), QBrush(QPixmap(":/background/Resources/background/ground.png")));
}

void ShopBoard::initialSelectedCharacter()
{
	const auto current = account->getSelectedCharacter();
	for (auto it : commodities)
	{
		if (it->getCharacterWidget()->getCharacter()->name == current->name)
		{
			it->getSelectButton()->setEnabled(false);
			//it->getSelectButton()->setIcon(QIcon(":/button/Resources/button/NO_button.png"));
			
		}
		else
		{
			//it->getSelectButton()->setText("SELECT");
		}
	}
}

void ShopBoard::initialMainWidget()
{
	initialLayoutMain();
}

void ShopBoard::initialStackWidget()
{
	for (auto it : messages)
		ui.stack->addWidget(it);
	ui.stack->setCurrentWidget(ui.page);
}

void ShopBoard::initialVectors()
{
	commodities.clear();
	messages.clear();
	auto map = CharacterManager::getInstance()->characters;
	for (auto it : map) {
		auto tempCommodity = new CommodityWidget(this, it);
		commodities.push_back(tempCommodity);
		connect(tempCommodity->getCharacterWidget(), SIGNAL(showMessage(QString)), this, SLOT(displayMessage(QString)));
		connect(tempCommodity, SIGNAL(updateSelect()), this, SLOT(updateSelectedCharacter()));
		connect(tempCommodity, SIGNAL(updateMoney()), this, SLOT(updateMoney()));
		auto tempMessage = new MessageWidget(this, it);
		messages.insert(it->name, tempMessage);
		connect(tempMessage, SIGNAL(deleteSignal()), this, SLOT(deleteMessage()));
	}
}

void ShopBoard::initialLayoutMain()
{
	ui.layout->setVerticalSpacing(20);
	ui.layout->setHorizontalSpacing(16);
	auto count = 0;
	while (count < commodities.size())
	{
		commodities[count]->setMaximumSize(120, 240);
		ui.layout->addWidget(commodities[count], count / 4, count % 4, 1, 1);
		count++;
	}
}


void ShopBoard::initialMoney()
{
	ui.moneyLabel->setText(QString::number(account->money));
}

void ShopBoard::displayMessage(const QString& character)
{
	ui.stack->setCurrentWidget(messages[character]);
}

void ShopBoard::deleteMessage()
{
	ui.stack->setCurrentWidget(ui.page);
}

void ShopBoard::updateSelectedCharacter()
{
	const auto current = account->getSelectedCharacter();
	for (auto it : commodities)
	{
		const auto currentName = it->getCharacterWidget()->getCharacter()->name;
		if (currentName != current->name)
		{
			it->getSelectButton()->setIcon(canSelect);
			if (account->hasBoughtCharacter(currentName))
			{
				it->getSelectButton()->setEnabled(true);
			}
		}
	}
}

void ShopBoard::updateMoney()
{
	ui.moneyLabel->setText(QString::number(account->money));
}

void ShopBoard::backToMainScene()
{
	QTimer::singleShot(500, this, [=]() {
		emit mainScene();
	});
}
