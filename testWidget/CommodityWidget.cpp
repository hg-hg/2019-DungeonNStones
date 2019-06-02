#include "stdafx.h"
#include "CommodityWidget.h"

CommodityWidget::CommodityWidget(QWidget *parent, Character * character, Account * account)
	: QWidget(parent)
{
	setCharacterWidget(character);
	setAccount(account);
	initialButton();
	initialLayout();
	initialBuyEvent();
}

CommodityWidget::~CommodityWidget()
{
}

QSize CommodityWidget::sizeHint() const
{
	return originSzie;
}

void CommodityWidget::setCharacterWidget(Character * character)
{
	this->characterWidget = new CharacterWidget(this, character);
}

void CommodityWidget::setAccount(Account * account)
{
	this->account = account;
}

CharacterWidget * CommodityWidget::getCharacterWidget()
{
	return characterWidget;
}

SelectButton * CommodityWidget::getSelectButton()
{
	return selectButton;
}

BuyButton * CommodityWidget::getBuyButton()
{
	return buyButton;
}

void CommodityWidget::initialButton()
{
	buyButton = new BuyButton(this);
	selectButton = new SelectButton(this);
	if (account->hasBoughtCharacter(characterWidget->getCharacter()->name))
	{
		buyButton->setText("Already Own");
		buyButton->setEnabled(false);
	}
	else 
	{
		buyButton->setText(QString::number(characterWidget->getCharacter()->price));
		selectButton->setEnabled(false);
	}
}


void CommodityWidget::initialLayout()
{
	auto layout = new QGridLayout;
	layout->setRowMinimumHeight(1, 30);
	layout->setVerticalSpacing(10);
	layout->addWidget(characterWidget, 0, 0, 1, 1);
	layout->addWidget(buyButton, 1, 0, 1, 1);
	layout->addWidget(selectButton, 2, 0, 1, 1);
	this->setLayout(layout);
}

void CommodityWidget::initialBuyEvent()
{
	connect(buyButton, SIGNAL(buySignal()), this, SLOT(mouseClickedBuy()));
	connect(selectButton, SIGNAL(selectSignal()), this, SLOT(mouseClickedSelect()));
}

void CommodityWidget::initialBuyConfirmMessage()
{
	QMessageBox msg(this);
	msg.setWindowTitle("Confirm");
	msg.setText("Sure to buy?");
	msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

	if (msg.exec() == QMessageBox::Ok)
	{
		QString name = characterWidget->getCharacter()->name;
		int cost = characterWidget->getCharacter()->price;
		if (account->buyCharacter(name, cost))
		{
			buyButton->setText("Already Own");
			buyButton->setEnabled(false);
			selectButton->setEnabled(true);
			emit updateMoney();
		}
		else
		{
			QMessageBox noEnoughMoney(this);
			noEnoughMoney.setWindowTitle("Message");
			noEnoughMoney.setText("You don't have enough money");
			noEnoughMoney.setStandardButtons(QMessageBox::Ok);
			noEnoughMoney.exec();
		}
	}
}

void CommodityWidget::initialSelectConfirmMessage()
{
	QMessageBox msg(this);
	msg.setWindowTitle("Confirm");
	msg.setText("Sure to select?");
	msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	if (msg.exec() == QMessageBox::Ok) 
	{
		QString name = characterWidget->getCharacter()->name;
		account->setCharacter(name);
		selectButton->setText("Selected");
		selectButton->setEnabled(false);
	}
}

void CommodityWidget::mouseClickedSelect()
{
	initialSelectConfirmMessage();
	emit updateSelected();
}

void CommodityWidget::mouseClickedBuy()
{
	initialBuyConfirmMessage();
}