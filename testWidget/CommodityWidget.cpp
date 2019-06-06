#include "stdafx.h"
#include "CommodityWidget.h"

CommodityWidget::CommodityWidget(QWidget* parent, Character* character)
	: QWidget(parent)
{
	ui.setupUi(this);
	setCharacterWidget(character);
	initialButton();
}

CommodityWidget::~CommodityWidget()
{
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
		//ui.cost->setText(QString::number(ui.characterWidget->getCharacter()->price));
		//ui.selectButton->setEnabled(false);
	}
}

void CommodityWidget::initialBuyConfirmMessage()
{
	QMessageBox msg(this);
	msg.setWindowTitle("Confirm");
	msg.setText("Sure to buy?");
	msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);

	if (msg.exec() == QMessageBox::Ok)
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
	//msg.setWindowFlag(Qt::FramelessWindowHint);
	msg.setText("Sure to select?");
	msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	if (msg.exec() == QMessageBox::Ok)
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
