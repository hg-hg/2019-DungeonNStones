#include "stdafx.h"
#include "PVE.h"
#include "CharacterManager.h"
#include <QTimer>
PVE::PVE(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//Account * account = Account::getInstance();
	ui.stackedWidget->setCurrentWidget(ui.playing);
	//ui.toast->setCurrentWidget(ui.escapePage);
	connect(ui.gameBoard, SIGNAL(sendPlayerDead(QString)), this, SLOT(playerDead(QString)));
	ui.gameBoard->setData(CharacterManager::getInstance()->getCharacter("AutoRobot"));
	ui.gameBoard->setLocalGame(true);
}

PVE::~PVE()
{
	qDebug();
}

void PVE::confirm()
{
	//ui.toast->setCurrentWidget(ui.continuePage);
}

void PVE::escape()
{
	QMessageBox msg(this);
	msg.setWindowTitle("escape");
	msg.setText("are you sure?");
	msg.setStandardButtons(QMessageBox::Ok | QMessageBox::Cancel);
	if (msg.exec() == QMessageBox::Ok) emit mainScene();
}

void PVE::continueGame()
{
	ui.gameBoard->restart();
	ui.stackedWidget->setCurrentWidget(ui.playing);
	//ui.toast->setCurrentWidget(ui.escapePage);
}

void PVE::quitGame()
{
	emit mainScene();
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
