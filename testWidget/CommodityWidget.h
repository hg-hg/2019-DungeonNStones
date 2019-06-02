#pragma once

#include <QWidget>
#include <QPushButton>
#include <QGridLayout>
#include <QMessageBox>
#include "BuyButton.h"
#include "SelectButton.h"
#include "Account.h"
#include "CharacterWidget.h"

class CommodityWidget : public QWidget
{
	Q_OBJECT

public:
	CommodityWidget(QWidget *parent, Character * character,Account * account);
	~CommodityWidget();
	QSize sizeHint() const override;
	void setCharacterWidget(Character * character);
	void setAccount(Account * account);
	CharacterWidget * getCharacterWidget();
	SelectButton * getSelectButton();
	BuyButton * getBuyButton();
private:
	void initialButton();
	void initialLayout();
	void initialBuyEvent();
	void initialBuyConfirmMessage();
	void initialSelectConfirmMessage();
signals:
	void updateSelected();
signals:
	void updateMoney();
private slots:
	void mouseClickedBuy();
	void mouseClickedSelect();
private:
	CharacterWidget * characterWidget;
	BuyButton * buyButton;
	SelectButton * selectButton;
	QSize originSzie = QSize(120, 200);
	Account * account;
};
