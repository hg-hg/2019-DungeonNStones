#include "stdafx.h"
#include "PVP.h"
#include "ConfirmBox.h"
#include "Client.h"
#include "Account.h"

Account* account = Account::getInstance();


PVP::PVP(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.gameBoard->setLocalGame(false);
	ui.stackedWidget->setCurrentWidget(ui.waiting);
	Client* client = Client::getInstance();
	connect(client, SIGNAL(gameStart(QString, QString)), this, SLOT(startGame(QString, QString)));
	connect(client, SIGNAL(enemyDisconnect()), this, SLOT(enemyDisconnected()));
	connect(client, SIGNAL(dead(QString)), this, SLOT(die(QString)));
	client->sendWaitForGame(account->name, account->getSelectedCharacter()->name);
}

PVP::~PVP()
{
}

void PVP::enemyDisconnected()
{
	ui.stackedWidget->setCurrentWidget(ui.gameOver);
	ui.hint->setText("enemy escape");
	ui.winner->setText("you wins");
}

void PVP::continueMatching()
{
	
	ui.stackedWidget->setCurrentWidget(ui.waiting);
	Client::getInstance()->sendWaitForGame(account->name, account->getSelectedCharacter()->name);
}

void PVP::escape()
{
	ui.pushButton->setPicture("");
	auto c = new ConfirmBox(this);
	c->setText("Are you sure?");
	if (c->exec() == 0) return;
	Client::getInstance()->sendEscapeGame();
	quitGame();
}

void PVP::stopMatching()
{
	auto c = new ConfirmBox(this);
	c->setText("Are you sure?");
	if (c->exec() == 0) return;
	Client::getInstance()->sendStopMatching();
	quitGame();
}

void PVP::quitGame()
{
	emit mainScene();
}

void PVP::die(const QString dead)
{
	ui.stackedWidget->setCurrentWidget(ui.gameOver);
	QString whoDead = "enemy dead", winner = "you win";
	if (account->name == dead)
	{
		whoDead = "you dead";
		winner = "enemy win";
	}
	ui.winner->setText(winner);
	ui.hint->setText(whoDead);
}

void PVP::startGame(const QString& account, const QString& character)
{
	ui.stackedWidget->setCurrentWidget(ui.playing);
	if (started) return;
	ui.gameBoard->gameStart(account, character);
	started = true;
}
