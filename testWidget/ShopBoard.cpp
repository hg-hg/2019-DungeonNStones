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
	initialEvent();
	initialSelectedCharacter();
	initialMoney();
	ui.backToMain->setPicture(".//Picture//back.bmp");
}

ShopBoard::~ShopBoard()
{
}

void ShopBoard::initialSelectedCharacter()
{
	auto current = account->getSelectedCharacter();
	for (auto it : commodities)
	{
		if (it->getCharacterWidget()->getCharacter()->name == current->name)
		{
			it->getSelectButton()->setText("Selected");
			it->getSelectButton()->setEnabled(false);
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
		auto tempMessage = new MessageWidget(this, it);
		messages.insert(it, tempMessage);
	}
}

void ShopBoard::initialLayoutMain()
{
	ui.layout->setVerticalSpacing(20);
	ui.layout->setHorizontalSpacing(16);
	int count = 0;
	while (count < commodities.size())
	{
		commodities[count]->setMaximumSize(130, 240);
		ui.layout->addWidget(commodities[count], count / 4, count % 4, 1, 1);
		count++;
	}
}

void ShopBoard::initialEvent()
{
	for (auto it : commodities)
	{
		connect(it->getCharacterWidget(), SIGNAL(showMessage(CharacterWidget *)), this, SLOT(displayMessage(CharacterWidget*)));
		connect(it, SIGNAL(updateSelected()), this, SLOT(updateSelectedCharacter()));
		connect(it, SIGNAL(updateMoney()), this, SLOT(updateMoney()));
	}
	for (auto it : messages)
		connect(it->getReturnButton(), SIGNAL(returnSignal()), this, SLOT(deleteMessage()));
}

void ShopBoard::initialMoney()
{
	ui.moneyEdit->setText(QString::number(account->money));
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
	auto current = account->getSelectedCharacter();
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
	ui.moneyEdit->setText(QString::number(account->money));
}

void ShopBoard::backToMainScene()
{
	ui.backToMain->ZoomPush();
	ui.backToMain->ZoomPop();
	QTimer::singleShot(500, this, [=]() {
		emit mainScene();
	});
}
