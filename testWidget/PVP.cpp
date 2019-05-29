#include "stdafx.h"
#include "PVP.h"
#include "Client.h"
#include "Account.h"

Account* account = Account::getInstance();
Client* client = Client::getInstance();

PVP::PVP(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	client->connectToServer();
	client->sendWaitForGame(account->name, account->getSelectedCharacter()->name);
	connect(client, SIGNAL(gameStart(QString, QString)), this, SLOT(gameStart(QString, QString)));
	
}

PVP::~PVP()
{
}

void PVP::gameStart(QString account, QString character)
{
	ui.stack->setCurrentWidget(ui.playing);
	ui.playing->gameStart(account, character);
}
