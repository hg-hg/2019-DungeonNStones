#pragma once

#include <QWidget>
#include <QMessageBox>
#include "ui_CommodityWidget.h"
#include "Character.h"
#include "Account.h"
#include "CharacterWidget.h"
#include "MainSceneButton.h"
class CommodityWidget : public QWidget
{
	Q_OBJECT

public:
	CommodityWidget(QWidget *parent, Character * character, Account * account);
	~CommodityWidget();
	void setCharacterWidget(Character * character);
	void setAccount(Account * account);
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
	Account * account;
};
