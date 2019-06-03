#include "stdafx.h"
#include "GameBoard.h"
#include "Client.h"
#include "CharacterManager.h"

void GameBoard::gameStart(const QString enemy, const QString enemyCharacter)
{
	enemyAccount = enemy;
	setData(CharacterManager::getInstance()->getCharacter(enemyCharacter));
}

GameBoard::GameBoard(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.gameCore->account = Account::getInstance()->name;
	//connect(Client::getInstance(), SIGNAL(gameStart(QString, QString)), this, SLOT(gameStart(QString, QString)));
	connect(ui.gameCore, SIGNAL(stonesCrushing(int, int, int, QString)), ui.player,
	        SLOT(stoneCrush(int, int, int, QString)));
	connect(ui.gameCore, SIGNAL(stonesCrushing(int, int, int, QString)), ui.enemy,
	        SLOT(stoneCrush(int, int, int, QString)));
}

void GameBoard::setLocalGame(const bool flag)
{
	localGame = flag;
	connect(ui.player, SIGNAL(useSkill(QString, QString)), ui.gameCore, SLOT(useSkill(QString, QString)));
	connect(ui.player, SIGNAL(dead(QString)), this, SLOT(playerDead(QString)));
	if (localGame)
	{
		const auto gs = new GameServer(this);

		//for auto robot
		connect(ui.enemy, SIGNAL(useSkill(QString, QString)), ui.gameCore, SLOT(useSkill(QString, QString)));
		connect(ui.enemy, SIGNAL(dead(QString)), this, SLOT(playerDead(QString)));

		connect(ui.player, SIGNAL(sendInfo(QString, int, int, int)), gs, SLOT(receiveInfo(QString, int, int, int)));
		connect(ui.enemy, SIGNAL(sendInfo(QString, int, int, int)), gs, SLOT(receiveInfo(QString, int, int, int)));
		connect(gs, SIGNAL(sendInfo(QString, int, int, int)), ui.player, SLOT(receiveInfo(QString, int, int, int)));
		connect(gs, SIGNAL(sendInfo(QString, int, int, int)), ui.enemy, SLOT(receiveInfo(QString, int, int, int)));
	}
	else
	{
		Client* client = Client::getInstance();
		connect(ui.player, SIGNAL(sendInfo(QString, int, int, int)), client,
		        SLOT(sendGameData(QString, int, int, int)));
		connect(client, SIGNAL(gameData(QString, int, int, int)), ui.player, SLOT(receiveInfo(QString, int, int, int)));
		connect(client, SIGNAL(gameData(QString, int, int, int)), ui.enemy, SLOT(receiveInfo(QString, int, int, int)));
		connect(ui.player, SIGNAL(dead(account)), this, SLOT(playerDead(QString)));
	}
}

void GameBoard::playerDead(QString playerAccount)
{
	ui.enemy->setGamePause(true);
	ui.player->setGamePause(true);
	Account* account = Account::getInstance();
	if (playerAccount == account->name) account->addMoney(300);
	else account->addMoney(1000);
	if (localGame) emit sendPlayerDead(playerAccount);
	else Client::getInstance()->sendDead(account->name);
}

void GameBoard::restart()
{
	ui.gameCore->fillBoard();
	ui.player->initialStatus();
	ui.enemy->initialStatus();
}

GameBoard::~GameBoard()
{
}

void GameBoard::setData(Character* enemyCha)
{
	auto account = Account::getInstance();
	ui.player->setAccount(account->name);
	ui.player->setCharacter(account->getSelectedCharacter());
	ui.enemy->setAccount(enemyAccount);
	ui.enemy->setAsEnemy();
	ui.enemy->setCharacter(enemyCha);
}
