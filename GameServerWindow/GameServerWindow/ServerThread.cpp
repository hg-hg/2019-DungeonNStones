#include "stdafx.h"
#include "serverthread.h"

ServerThread::ServerThread(int sockDesc, QObject* parent)
	: QThread(parent), sockDesc(sockDesc)
{
}

ServerThread::~ServerThread()
{
	quit();
	wait();

	socket->close();
	socket->deleteLater();
}

void ServerThread::run()
{
	socket = new MySocket(sockDesc);

	if (!socket->setSocketDescriptor(sockDesc)) return;


	connect(socket, &MySocket::disconnected, this, &ServerThread::disconnectToHost);
	connect(socket, SIGNAL(waitForGame(QString, QString)), this, SLOT(clientWaitForGame(QString, QString)));
	connect(socket, SIGNAL(clientGameData(QString)), this, SLOT(gameData(QString)));
	connect(socket, SIGNAL(clientEscapeGame()), this, SLOT(escapeGame()));
	connect(socket, SIGNAL(clientStopMatching()), this, SLOT(stopMatching()));
	connect(socket, SIGNAL(clientDead(QString)), this, SLOT(clientDie(QString)));
	exec();
}

void ServerThread::sendMessage(const int sockDest, const QString data)
{
	if (sockDest != sockDesc) return;
	if (data.isEmpty()) { return; }
	qDebug() << sockDest << " " << data;
	socket->sendMessage(data);
}

void ServerThread::clientWaitForGame(const QString account, const QString character)
{
	emit threadWaitForGame(account, character);
}

void ServerThread::gameStart(const QString enemyAccount, const QString enemyCharacter)
{
	socket->gameStart(enemyAccount, enemyCharacter);
}

void ServerThread::gameData(const QString data)
{
	//emit threadGameData(data);
	enemy->sendMessage(enemy->sockDesc, data);
	sendMessage(sockDesc, data);
}

void ServerThread::escapeGame()
{
	emit clientEscape();
}

void ServerThread::stopMatching()
{
	emit clientStopMatching();
}

void ServerThread::clientDie(QString account)
{
	emit clientDead(account);
}

void ServerThread::disconnectToHost()
{
	socket->disconnectFromHost();
	emit disconnectTCP(sockDesc);
}
