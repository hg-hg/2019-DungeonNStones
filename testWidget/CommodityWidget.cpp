#include "stdafx.h"
#include "CommodityWidget.h"
#include "ConfirmBox.h"
CommodityWidget::CommodityWidget(QWidget* parent, Character* character)
	: QWidget(parent)
{
	ui.setupUi(this);
	setCharacterWidget(character);
	initialButton();
}

CommodityWidget::~CommodityWidget()
{
	qDebug();
}

void CommodityWidget::setCharacterWidget(Character * character)
{
	ui.characterWidget->setCharacter(character);
}

CharacterWidget * CommodityWidget::getCharacterWidget()
{
	return ui.characterWidget;
}



MainSceneButton * CommodityWidget::getSelectButton()
{
	return ui.selectButton;
}

MainSceneButton * CommodityWidget::getBuyButton()
{
	return ui.buyButton;
}

void CommodityWidget::initialButton()
{
	if (account->hasBoughtCharacter(ui.characterWidget->getCharacter()->name))
	{
		ui.buyButton->setEnabled(false);
	}
	else
	{
		ui.selectButton->setVisible(false);
	}
}

void CommodityWidget::initialBuyConfirmMessage()
{   
	auto c = new ConfirmBox(this);
	
	c->setText("Sure to buy ?");
	if (c->exec() == 1)
	{
		const auto name = ui.characterWidget->getCharacter()->name;
		const auto cost = ui.characterWidget->getCharacter()->price;
		if (account->buyCharacter(name, cost))
		{
			ui.buyButton->setEnabled(false);
			ui.selectButton->setVisible(true);
			ui.selectButton->setIcon(canSelect);
			ui.selectButton->setEnabled(true);
			emit updateMoney();
		}
		else
		{
			auto noEnoughMoney = new ConfirmBox(this);
			noEnoughMoney->setText("No enough money !");
			noEnoughMoney->exec();
		}
	}
}

void CommodityWidget::initialSelectConfirmMessage()
{

	auto c = new ConfirmBox(this);
	c->setText("Sure to select ?");
	if (c->exec() == 1)
	{
		const auto name = ui.characterWidget->getCharacter()->name;
		account->setCharacter(name);
		ui.selectButton->setEnabled(false);
		emit updateSelect();
	}

}

void CommodityWidget::mouseClickedBuy()
{
	initialBuyConfirmMessage();
}

void CommodityWidget::mouseClickedSelect()
{
	initialSelectConfirmMessage();
	
}
