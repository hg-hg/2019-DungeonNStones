#include "stdafx.h"
#include "Login.h"
#include "Client.h"
#include <QKeyEvent>


Login::Login(QWidget *parent)
	: QWidget(parent)
{
	
	ui.setupUi(this);
	ui.stackedWidget->setCurrentWidget(ui.enterAccount);
	connect(Client::getInstance(), SIGNAL(accountInitialized()), this, SLOT(accountInitialized()));
}

Login::~Login()
{
	qDebug();
}

void Login::keyPressEvent(QKeyEvent * event)
{
	if (event->key() == Qt::Key_Return)
	{
		Client::getInstance()->requestAccount(ui.account->text());
		ui.stackedWidget->setCurrentWidget(ui.waiting);
	}
}

void Login::accountInitialized()
{
	emit mainScene();
}

void Login::loginToServer()
{
	Client::getInstance()->requestAccount(ui.account->text());
	ui.stackedWidget->setCurrentWidget(ui.waiting);
}
