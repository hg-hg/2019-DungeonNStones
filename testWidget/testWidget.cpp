#include "stdafx.h"
#include "testWidget.h"
#include "Client.h"
Client * client = Client::getInstance();

testWidget::testWidget(QWidget *parent)
	: QMainWindow(parent)
{
	//am->setCurrentAccount("yuri");
	//wtf
	//account = am->getCurrentAccount();
	client->connectToServer();
	client->requestAccount("wtf");
	
	qDebug() << Account::getInstance()->name;
	ui.setupUi(this);
	
	//ui.gameBoard->setData(account, account->getSelectedCharacter(), cm->getCharacter("Test2"));
	
}

