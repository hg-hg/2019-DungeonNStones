#include "stdafx.h"
#include "PVE.h"
#include "Account.h"
#include "CharacterManager.h"

PVE::PVE(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//Account * account = Account::getInstance();
	ui.stackedWidget->setCurrentWidget(ui.playing);
	connect(ui.gameBoard, SIGNAL(sendPlayerDead(QString)), this, SLOT(playerDead(QString)));
	ui.gameBoard->setData(CharacterManager::getInstance()->getCharacter("AutoRobot"));
	ui.gameBoard->setLocalGame(true);
}

PVE::~PVE()
{
}

void PVE::confirm()
{
	QMessageBox msg(this);
	msg.setWindowTitle("Game is Over");
	msg.setText("again?");
	msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	if (msg.exec() == QMessageBox::Ok) {
		ui.gameBoard->restart();
		ui.stackedWidget->setCurrentWidget(ui.playing);
	}
	else {
		emit mainScene();
	}
}

void PVE::escape()
{
	QMessageBox msg(this);
	msg.setWindowTitle("escape");
	msg.setText("are you sure?");
	msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	if (msg.exec() == QMessageBox::Ok) emit mainScene();
}

void PVE::playerDead(QString playerAccount)
{
	ui.stackedWidget->setCurrentWidget(ui.gameOver);
	QString moviePath;
	if (playerAccount == ui.gameBoard->enemyAccount) {
		//moviePath = "./";
		ui.movie->setText("you win");
	}
	else {
		//moviePath = "./";
		ui.movie->setText("huaji win");
	}
	//QMovie* m = new QMovie(moviePath);
	//ui.movie->setMovie(m);
	QTimer::singleShot(500, this, [=]() {
		//change display movie time 500ms
		confirm();
	});
	
}
