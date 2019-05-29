#include "stdafx.h"
#include "GameServer.h"

GameServer::GameServer(QObject *parent)
	: QObject(parent)
{
}

GameServer::~GameServer()
{
}

void GameServer::receiveInfo(QString account, int hp, int damage, int mp)
{
	emit sendInfo(account, hp, damage, mp);
	//Client::getInstance()->sendGameData(account, hp, damage, mp);
}
