#include "stdafx.h"
#include "testWidget.h"
#include "Client.h"
#include "PVE.h"
#include "PVP.h"
#include "ShopBoard.h"
Client * client = Client::getInstance();

testWidget::testWidget(QWidget *parent)
	: QMainWindow(parent)
{
	//am->setCurrentAccount("yuri");
	//wtf
	//account = am->getCurrentAccount();
	client->connectToServer();
	//获得了Account名
	//client->requestAccount("yuri");
	
	//qDebug() << Account::getInstance()->name;
	ui.setupUi(this);
	connect(ui.login, SIGNAL(mainScene()), this, SLOT(mainScene()));
	connect(ui.mainScene, SIGNAL(goPVP()), this, SLOT(pvp()));
	connect(ui.mainScene, SIGNAL(goPVE()), this, SLOT(pve()));
	connect(ui.mainScene, SIGNAL(goShop()), this, SLOT(shop()));
	connect(ui.mainScene, SIGNAL(goSetting()), this, SLOT(setting()));
	connect(ui.mainScene, SIGNAL(goQuit()), this, SLOT(quit()));
	//ui.gameBoard->setData(account, account->getSelectedCharacter(), cm->getCharacter("Test2"));
	
}

void testWidget::closeEvent(QCloseEvent * event)
{
	client->sendDisconnecting();
}

void testWidget::pvp()
{
	PVP * pvp = new PVP(this);
	ui.stackedWidget->addWidget(pvp);
	ui.stackedWidget->setCurrentWidget(pvp);
}

void testWidget::pve()
{
	PVE * pve = new PVE(this);
	ui.stackedWidget->addWidget(pve);
	ui.stackedWidget->setCurrentWidget(pve);
}

void testWidget::shop()
{
	auto shopBoard = new ShopBoard(this);
	ui.stackedWidget->addWidget(shopBoard);
	ui.stackedWidget->setCurrentWidget(shopBoard);
}

void testWidget::quit()
{
}

void testWidget::setting()
{
}

void testWidget::mainScene()
{
	auto toDelete = static_cast<QWidget*>(sender());
	ui.stackedWidget->removeWidget(toDelete);
	toDelete->deleteLater();
	ui.stackedWidget->setCurrentWidget(ui.mainScene);
}
