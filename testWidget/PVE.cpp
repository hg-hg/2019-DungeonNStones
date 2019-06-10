#include "stdafx.h"
#include "PVE.h"
#include "CharacterManager.h"
#include "ConfirmBox.h"
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
	auto c = new ConfirmBox(this);
	c->setText("Are you sure?");
	if (c->exec() == 1) emit mainScene();
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
		moviePath = ":/skin/Resources/skin/" + Account::getInstance()->getSelectedCharacter()->skin;
		const auto movie = new QMovie(this);
		movie->setFileName(moviePath);
		ui.movie->setMovie(movie);
		movie->start();
	}
	else {
		ui.movie->setPixmap(QPixmap(":/word/Resources/word/newBee.png"));
	}
	QTimer::singleShot(500, this, [=]() {
		//change display movie time 500ms
		confirm();
	});
	
}
