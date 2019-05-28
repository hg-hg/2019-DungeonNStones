#pragma once

#include <QtWidgets/QMainWindow>
#include "GameLogic.h"
#include "Player.h"

#include "AccountManager.h"
#include "ui_testWidget.h"



class testWidget : public QMainWindow
{
	Q_OBJECT

public:
	testWidget(QWidget *parent = Q_NULLPTR);

protected:
	
private:
	Ui::testWidgetClass ui;
	//CharacterManager* cm = new CharacterManager(this);
	CharacterManager* cm = CharacterManager::getInstance();
	AccountManager* am = new AccountManager();
	Account* account = Account::getInstance();
};
