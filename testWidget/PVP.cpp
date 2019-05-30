#include "stdafx.h"
#include "PVP.h"
#include "Client.h"
#include "Account.h"

Account* account = Account::getInstance();


PVP::PVP(QWidget *parent)
	: QWidget(parent)
{
	Client* client = Client::getInstance();
	connect(client, SIGNAL(gameStart(QString, QString)), this, SLOT(gameStart(QString, QString)));
	client->sendWaitForGame(account->name, account->getSelectedCharacter()->name);
	ui.setupUi(this);
	ui.playing->setLocalGame(false);
	
}

PVP::~PVP()
{
}

void PVP::gameStart(QString account, QString character)
{
	ui.stack->setCurrentWidget(ui.playing);
	ui.playing->gameStart(account, character);
}
