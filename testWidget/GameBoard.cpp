#include "stdafx.h"
#include "GameBoard.h"


GameBoard::GameBoard(QWidget* parent)
	:QWidget(parent)
{
	ui.setupUi(this);
	connect(ui.gameCore, SIGNAL(stonesCrushing(int, int, int)), ui.player, SLOT(stoneCrush(int, int, int)));
	gs = new GameServer(this);
	connect(ui.player, SIGNAL(useSkill(QString)), ui.gameCore, SLOT(useSkill(QString)));
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
