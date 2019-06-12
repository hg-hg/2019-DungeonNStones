#pragma once

#include <QWidget>
#include "ui_GameBoard.h"
#include "GameLogic.h"
#include "Player.h"
#include "AccountManager.h"
#include "GameServer.h"


class GameBoard : public QWidget
{
	Q_OBJECT

public slots:
	void gameStart(QString enemy, QString enemyCharacter);
	void playerDead(QString playerAccount);
	void restart();

private slots:
	void makeBoardFilledAgain();
signals:
	void sendPlayerDead(QString playerAccount);

public:
	GameBoard(QWidget *parent = Q_NULLPTR);
	~GameBoard();
	void setLocalGame(bool flag);
	void setData(Character* enemyCha);

public:
	QString enemyAccount = "enemy";
private:
	Ui::GameBoard ui;
	bool localGame;
};
