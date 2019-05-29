#include "stdafx.h"
#include "testWidget.h"

testWidget::testWidget(QWidget *parent)
	: QMainWindow(parent)
{
	am->setCurrentAccount("yuri");
	account = am->getCurrentAccount();
	ui.setupUi(this);
	
	//ui.gameBoard->setData(account, account->getSelectedCharacter(), cm->getCharacter("Test2"));
	qDebug() << Account::getInstance()->name;
}

