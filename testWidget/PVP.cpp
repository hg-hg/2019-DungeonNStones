#include "stdafx.h"
#include "PVP.h"
#include "Client.h"
#include "Account.h"
#include <QTimer>
Account* account = Account::getInstance();


PVP::PVP(QWidget* parent)
	: QWidget(parent)
{
	Client* client = Client::getInstance();
	connect(client, SIGNAL(gameStart(QString, QString)), this, SLOT(startGame(QString, QString)));
	connect(client, SIGNAL(enemyDisconnect()), this, SLOT(enemyDisconnected()));
	connect(client, SIGNAL(dead(QString)), this, SLOT(die(QString)));
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
	ui.pushButton->setPicture("");
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

void PVP::die(const QString dead)
{
	ui.mainStack->setCurrentWidget(ui.dead);
	QString whoDead = "enemy dead", winner = "you win";
	if (account->name == dead)
	{
		whoDead = "you dead";
		winner = "enemy win";
	}
	ui.winner->setText(winner);
	ui.whoDead->setText(whoDead);
	ui.toast->setCurrentWidget(ui.gameOver);
}

void PVP::startGame(const QString& account, const QString& character)
{
	ui.mainStack->setCurrentWidget(ui.playing);
	ui.toast->setCurrentWidget(ui.escape);
	if (started) return;
	ui.playing->gameStart(account, character);
	started = true;
}
