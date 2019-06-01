#pragma once

#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include "Account.h"
#include "CommodityWidget.h"
#include "MessageWidget.h"

class ShopBoard : public QWidget
{
	Q_OBJECT

public:
	ShopBoard(QWidget *parent);
	~ShopBoard();
	QSize sizeHint() const override;
	void setAccount(Account * account);
	Account* getAccount();
private:
	void initialMainWidget();
	void initialStackWidget();
	void intialVectors();
	void initialLayoutMain();
	void initialEvent();
private slots:
	void displayMessage(CharacterWidget * current);
	void deleteMessage();
	void updateSelectedCharacter();
public:
	QWidget * mainWidget;
	QVector<CommodityWidget *> containers;
	QMap<Character *, MessageWidget *> messages;
	Account* account = Account::getInstance();
	QStackedWidget * stack;
	QPushButton * returnButton;
};
