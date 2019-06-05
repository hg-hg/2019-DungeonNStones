#include "stdafx.h"
#include "testWidget.h"
#include "Client.h"
#include "PVE.h"
#include "PVP.h"
#include "ShopBoard.h"
#include "GameBoard.h"
#include "Setting.h"
#include "Sound.h"

Client * client = Client::getInstance();

testWidget::testWidget(QWidget *parent)
	: QMainWindow(parent)
{
	//am->setCurrentAccount("yuri");
	//wtf
	//account = am->getCurrentAccount();
	client->connectToServer();
	Sound::initialVolume();
	//获得了Account名
	//client->requestAccount("yuri");
	
	//qDebug() << Account::getInstance()->name;
	ui.setupUi(this);
	Sound sound;
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
	if (entered) quit();
}

void testWidget::moveToCenter()
{
	setFixedSize({ 1112, 641 });
	const auto deskRect = QApplication::desktop()->availableGeometry();
	this->move((deskRect.right() - 1112) / 2, (deskRect.bottom() - 641) / 2);
}

void testWidget::pvp()
{

	PVP * pvp = new PVP(this);
	moveToCenter();
	connect(pvp, SIGNAL(mainScene()), this, SLOT(mainScene()));
	ui.stackedWidget->addWidget(pvp);
	ui.stackedWidget->setCurrentWidget(pvp);
}

void testWidget::pve()
{
	PVE * pve = new PVE(this);
	moveToCenter();
	connect(pve, SIGNAL(mainScene()), this, SLOT(mainScene()));
	ui.stackedWidget->addWidget(pve);
	ui.stackedWidget->setCurrentWidget(pve);
}

void testWidget::shop()
{
	const auto shopBoard = new ShopBoard(this);
	connect(shopBoard, SIGNAL(mainScene()), this, SLOT(mainScene()));
	ui.stackedWidget->addWidget(shopBoard);
	ui.stackedWidget->setCurrentWidget(shopBoard);
}

void testWidget::quit()
{
	account->sendAccountInfo();
	Sound::writeFile();
	exit(0);
}

void testWidget::setting()
{
	const auto setting = new Setting(this);
	connect(setting, SIGNAL(mainScene()), this, SLOT(mainScene()));
	ui.stackedWidget->addWidget(setting);
	ui.stackedWidget->setCurrentWidget(setting);
}

void testWidget::mainScene()
{
	entered = true;
	setFixedSize({ 800, 600 });
	auto toDelete = static_cast<QWidget*>(sender());
	ui.stackedWidget->removeWidget(toDelete);
	toDelete->deleteLater();
	ui.stackedWidget->setCurrentWidget(ui.mainScene);
}
