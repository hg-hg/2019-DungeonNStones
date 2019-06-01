#include "stdafx.h"
#include "ShopBoard.h"
#include "CharacterWidget.h"

ShopBoard::ShopBoard(QWidget *parent)
	: QWidget(parent)
{
	setAccount(account);
	intialVectors();
	initialMainWidget();
	initialStackWidget();
	initialEvent();
}

ShopBoard::~ShopBoard()
{
}

QSize ShopBoard::sizeHint() const
{
	return QSize(600, 1000);
}

void ShopBoard::initialMainWidget()
{
	mainWidget = new QWidget();
	initialLayoutMain();
}

void ShopBoard::initialStackWidget()
{
	stack = new QStackedWidget();
	
	stack->addWidget(mainWidget);
	for (auto it : messages)
		stack->addWidget(it);

	auto layout = new QGridLayout();
	layout->addWidget(stack);
	this->setLayout(layout);
	stack->setCurrentWidget(mainWidget);
	//stack->setCurrentWidget(messages[containers[0]->getCharacterWidget()->getCharacter()]);
}

void ShopBoard::intialVectors()
{
	containers.clear();
	containers.resize(0);
	messages.clear();
	auto map = CharacterManager::getInstance()->characters;
	for (auto it : map) {
		auto temp = new CommodityWidget(this, it, account);
		containers.push_back(temp);
		auto temp2 = new MessageWidget(this, it);
		messages.insert(it,temp2);
	}
}

void ShopBoard::initialLayoutMain()
{
	auto layout = new QGridLayout();
	layout->setVerticalSpacing(20);
	layout->setHorizontalSpacing(16);
	int count = 0;
	while (count < containers.size()) 
	{
		containers[count]->setMaximumSize(130, 240);
		layout->addWidget(containers[count],count/4,count%4,1,1);
		count++;
	}
	mainWidget->setLayout(layout);
}

void ShopBoard::initialEvent()
{
	for (auto it : containers)
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
	stack->setCurrentWidget(messages[character]);
}

void ShopBoard::deleteMessage()
{
	stack->setCurrentWidget(mainWidget);
}

void ShopBoard::updateSelectedCharacter()
{
	auto current = account->getSelectedCharacter();
	for (auto it : containers) 
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

void ShopBoard::setAccount(Account * account)
{
	this->account = account;
}

Account * ShopBoard::getAccount()
{
	return this->account;
}

