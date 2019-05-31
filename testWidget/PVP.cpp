#include "stdafx.h"
#include "PVP.h"
#include "Client.h"
#include "Account.h"

Account* account = Account::getInstance();


PVP::PVP(QWidget *parent)
	: QWidget(parent)
{
	Client* client = Client::getInstance();
	connect(client, SIGNAL(gameStart(QString, QString)), this, SLOT(startGame(QString, QString)));
	connect(client, SIGNAL(enemyDisconnect()), this, SLOT(enemyDisconnected()));
	client->sendWaitForGame(account->name, account->getSelectedCharacter()->name);
	ui.setupUi(this);
	ui.playing->setLocalGame(false);
	ui.stack->setCurrentWidget(ui.waiting);
}

PVP::~PVP()
{
}

void PVP::enemyDisconnected()
{
	ui.stack->setCurrentWidget(ui.disconnect);
}

void PVP::startGame(QString account, QString character)
{
	ui.stack->setCurrentWidget(ui.playing);
	ui.playing->gameStart(account, character);
}
