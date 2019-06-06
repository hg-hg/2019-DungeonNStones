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

void ShopBoard::initialSelectedCharacter()
{
	const auto current = account->getSelectedCharacter();
	for (auto it : commodities)
	{
		if (it->getCharacterWidget()->getCharacter()->name == current->name)
		{
			it->getSelectButton()->setText("Selected");
			it->getSelectButton()->setEnabled(false);
		}
		else
		{
			it->getSelectButton()->setText("SELECT");
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
		auto tempCommodity = new CommodityWidget(this, it, account);
		commodities.push_back(tempCommodity);
		connect(tempCommodity->getCharacterWidget(), SIGNAL(showMessage(CharacterWidget *)), this, SLOT(displayMessage(CharacterWidget*)));
		connect(tempCommodity, SIGNAL(updateSelect()), this, SLOT(updateSelectedCharacter()));
		connect(tempCommodity, SIGNAL(updateMoney()), this, SLOT(updateMoney()));
		auto tempMessage = new MessageWidget(this, it);
		messages.insert(it, tempMessage);
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

//void ShopBoard::initialEvent()
//{
//	for (auto it : commodities)
//	{
//		connect(it->getCharacterWidget(), SIGNAL(showMessage(CharacterWidget *)), this, SLOT(displayMessage(CharacterWidget*)));
//		connect(it, SIGNAL(updateSelect()), this, SLOT(updateSelectedCharacter()));
//	}
//}

void ShopBoard::initialMoney()
{
	ui.moneyLabel->setText(QString::number(account->money));
}

void ShopBoard::displayMessage(CharacterWidget * current)
{
	Character * character = current->getCharacter();
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
		if (it->getCharacterWidget()->getCharacter()->name != current->name)
		{
			it->getSelectButton()->setText("SELECT");
			if (account->hasBoughtCharacter(it->getCharacterWidget()->getCharacter()->name))
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
	ui.backToMain->zoomPush();
	ui.backToMain->zoomPop();
	QTimer::singleShot(500, this, [=]() {
		emit mainScene();
	});
}
