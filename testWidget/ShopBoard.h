#pragma once

#include <QWidget>
#include "ui_ShopBoard.h"
#include "Account.h"
#include "CommodityWidget.h"
#include "MessageWidget.h"

class ShopBoard : public QWidget
{
	Q_OBJECT

public:
	ShopBoard(QWidget *parent = Q_NULLPTR);
	~ShopBoard();
private:
	void initialMainWidget();
	void initialStackWidget();
	void initialVectors();
	void initialLayoutMain();
	void initialEvent();
private slots:
	void displayMessage(CharacterWidget * current);
	void deleteMessage();
	void updateSelectedCharacter();
	void backToMainScene();

signals:
	void mainScene();
private:
	Ui::ShopBoard ui;
	QScrollArea * mainWidget;
	QVector<CommodityWidget *> commodities;
	QMap<Character *, MessageWidget *> messages;
	Account * account = Account::getInstance();
};
