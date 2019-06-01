#include "stdafx.h"
#include "ShopBoard.h"

ShopBoard::ShopBoard(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initialVectors();
	initialMainWidget();
	initialStackWidget();
	initialEvent();
	initialSelectedCharacter();
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
	mainWidget = new QScrollArea();
	initialLayoutMain();
}

void ShopBoard::initialStackWidget()
{
	ui.stack->addWidget(mainWidget);
	for (auto it : messages)
		ui.stack->addWidget(it);
	ui.stack->setCurrentWidget(mainWidget);
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
	auto layout = new QGridLayout();
	layout->setVerticalSpacing(20);
	layout->setHorizontalSpacing(16);
	int count = 0;
	while (count < commodities.size())
	{
		commodities[count]->setMaximumSize(130, 240);
		layout->addWidget(commodities[count], count / 4, count % 4, 1, 1);
		count++;
	}
	mainWidget->setLayout(layout);
}

void ShopBoard::initialEvent()
{
	for (auto it : commodities)
	{
		connect(it->getCharacterWidget(), SIGNAL(showMessage(CharacterWidget *)), this, SLOT(displayMessage(CharacterWidget*)));
		connect(it, SIGNAL(updateSelected()), this, SLOT(updateSelectedCharacter()));
	}
	for (auto it : messages)
		connect(it->getReturnButton(), SIGNAL(returnSignal()), this, SLOT(deleteMessage()));
}

void ShopBoard::displayMessage(CharacterWidget * current)
{
	Character * character = current->getCharacter();
	ui.stack->setCurrentWidget(messages[character]);
}

void ShopBoard::deleteMessage()
{
	ui.stack->setCurrentWidget(mainWidget);
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

void ShopBoard::backToMainScene()
{
	emit mainScene();
}
