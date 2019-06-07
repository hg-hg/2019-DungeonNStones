#pragma once

#include <QWidget>
#include "ui_CommodityWidget.h"
#include "Character.h"
#include "Account.h"
#include "CharacterWidget.h"
#include "MainSceneButton.h"
class CommodityWidget : public QWidget
{
	Q_OBJECT

public:
	CommodityWidget(QWidget *parent, Character * character);
	~CommodityWidget();
	void setCharacterWidget(Character * character);
	CharacterWidget * getCharacterWidget();
	MainSceneButton * getBuyButton();
	MainSceneButton * getSelectButton();

private:
	void initialButton();
	void initialBuyConfirmMessage();
	void initialSelectConfirmMessage();
signals:
	void updateSelect();
	void updateMoney();
private slots:
	void mouseClickedBuy();
	void mouseClickedSelect();
private:
	Ui::CommodityWidget ui;
	Account * account = Account::getInstance();

	QIcon canSelect = QIcon(":/button/Resources/button/YES_button.png");
	QIcon cannotSelect = QIcon(":/button/Resources/button/NO_button.png");
};
