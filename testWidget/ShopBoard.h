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

protected:
	void paintEvent(QPaintEvent* event) override;
private:
	void initialSelectedCharacter();
	void initialMainWidget();
	void initialStackWidget();
	void initialVectors();
	void initialLayoutMain();
	void initialMoney();
private slots:
	void displayMessage(const QString& character);
	void deleteMessage();
	void updateSelectedCharacter();
	void updateMoney();
	void backToMainScene();

signals:
	void mainScene();
private:
	Ui::ShopBoard ui;

	QVector<CommodityWidget *> commodities;
	QMap<QString, MessageWidget *> messages;
	Account * account = Account::getInstance();

	QIcon canSelect = QIcon(":/button/Resources/button/YES_button.png");
	QIcon cannotSelect = QIcon(":/button/Resources/button/NO_button.png");
};
