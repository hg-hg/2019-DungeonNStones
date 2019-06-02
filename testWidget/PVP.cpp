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
	ui.mainStack->setCurrentWidget(ui.waiting);
	ui.toast->setCurrentWidget(ui.matching);
}

PVP::~PVP()
{
}

void PVP::enemyDisconnected()
{
	ui.mainStack->setCurrentWidget(ui.disconnect);
	ui.toast->setCurrentWidget(ui.gameOver);
	ui.winner->setText("you wins");
}

void PVP::continueMatching()
{
	ui.toast->setCurrentWidget(ui.matching);
	ui.mainStack->setCurrentWidget(ui.waiting);
	Client::getInstance()->sendWaitForGame(account->name, account->getSelectedCharacter()->name);
}

void PVP::escape()
{
	QMessageBox msg(this);
	msg.setWindowTitle("escape");
	msg.setText("are you sure?");
	msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	if (msg.exec() == QMessageBox::Cancel) return;
	Client::getInstance()->sendEscapeGame();
	quitGame();
}

void PVP::stopMatching()
{
	QMessageBox msg(this);
	msg.setWindowTitle("stop matching");
	msg.setText("are you sure?");
	msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	if (msg.exec() == QMessageBox::Cancel) return;
	Client::getInstance()->sendStopMatching();
	quitGame();
}

void PVP::quitGame()
{
	emit mainScene();
}

void PVP::startGame(QString account, QString character)
{
	ui.mainStack->setCurrentWidget(ui.playing);
	ui.playing->gameStart(account, character);
	ui.toast->setCurrentWidget(ui.escape);
}
