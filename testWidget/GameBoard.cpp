#include "stdafx.h"
#include "GameBoard.h"
#include "Client.h"
#include "CharacterManager.h"

void GameBoard::gameStart(QString enemy, QString enemyCharacter)
{
	enemyAccount = enemy;
	setData(current, current->getSelectedCharacter(), CharacterManager::getInstance()->getCharacter(enemyCharacter));
}

GameBoard::GameBoard(QWidget* parent)
	:QWidget(parent)
{
	ui.setupUi(this);
	ui.gameCore->account = Account::getInstance()->name;
	connect(Client::getInstance(), SIGNAL(gameStart(QString, QString)), this, SLOT(gameStart(QString, QString)));
	connect(ui.gameCore, SIGNAL(stonesCrushing(int, int, int, QString)), ui.player, SLOT(stoneCrush(int, int, int, QString)));
	connect(ui.gameCore, SIGNAL(stonesCrushing(int, int, int, QString)), ui.enemy, SLOT(stoneCrush(int, int, int, QString)));
	gs = new GameServer(this);
	connect(ui.player, SIGNAL(useSkill(QString, QString)), ui.gameCore, SLOT(useSkill(QString, QString)));
	connect(ui.enemy, SIGNAL(useSkill(QString, QString)), ui.gameCore, SLOT(useSkill(QString, QString)));
	connect(ui.player, SIGNAL(sendInfo(QString, int, int, int)), gs, SLOT(receiveInfo(QString, int, int, int)));
	connect(ui.enemy, SIGNAL(sendInfo(QString, int, int, int)), gs, SLOT(receiveInfo(QString, int, int, int)));
	connect(gs, SIGNAL(sendInfo(QString, int, int, int)), ui.player, SLOT(receiveInfo(QString, int, int, int)));
	connect(gs, SIGNAL(sendInfo(QString, int, int, int)), ui.enemy, SLOT(receiveInfo(QString, int, int, int)));
}

GameBoard::~GameBoard()
{
}

void GameBoard::setData(Account * acct, Character * myCha, Character * enemyCha)
{
	current = acct;
	ui.player->setAccount(current->name);
	ui.player->setCharacter(myCha);
	ui.enemy->setAccount(enemyAccount);
	ui.enemy->setAsEnemy();
	ui.enemy->setCharacter(enemyCha);
}
