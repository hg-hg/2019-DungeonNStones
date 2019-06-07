#pragma once

#include <QtWidgets/QMainWindow>

#include "Client.h"
#include "AccountManager.h"
#include "ui_testWidget.h"



class testWidget : public QMainWindow
{
	Q_OBJECT

public:
	testWidget(QWidget *parent = Q_NULLPTR);

protected:
	void closeEvent(QCloseEvent *event) override;

private:
	void moveToCenter();

public slots:
	void mainScene();
	void pvp();
	void pve();
	void shop();
	void quit();
	void setting();
	
private:
	Ui::testWidgetClass ui;
	//CharacterManager* cm = new CharacterManager(this);
	CharacterManager* cm = CharacterManager::getInstance();
	AccountManager* am = new AccountManager();
	Account* account = Account::getInstance();
	Client* client = Client::getInstance();
	bool entered = false;
};
