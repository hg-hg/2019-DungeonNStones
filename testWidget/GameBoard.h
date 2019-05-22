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

public:
	GameBoard(QWidget *parent);
	~GameBoard();
	Account* current;
	void setData(Account* acct, Character* myCha, Character* enemyCha);
private:
	Ui::GameBoard ui;
	QString enemyAccount = "enemy";
	GameServer* gs;
};
