#include "stdafx.h"
#include "serverthread.h"

ServerThread::ServerThread(int sockDesc, QObject *parent)
	: QThread(parent),m_sockDesc(sockDesc)
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
	socket = new MySocket(m_sockDesc);

	if (!socket->setSocketDescriptor(m_sockDesc)) {
		return;
	}

	connect(socket, &MySocket::disconnected, this, &ServerThread::disconnectToHost);
	//connect(socket, SIGNAL(clientDisconncting()), this, SLOT(disconnectToHost()));
	/*connect(socket, SIGNAL(dataReady(const QString&, const QByteArray&)),
		this, SLOT(readMessage(const QString&, const QByteArray&)));*/

	//connect(this, SIGNAL(sendMessage(const QString&)), socket, SLOT(sendMessage(const QString&)));
	//connect(socket, SIGNAL(addAccount(QString)), this, SLOT(addAccount(QString)));
	connect(socket, SIGNAL(waitForGame(QString, QString)), this, SLOT(clientWaitForGame(QString, QString)));
	connect(socket, SIGNAL(clientGameData(QString)), this, SLOT(gameData(QString)));
	exec();
}

void ServerThread::sendMessage(int sockDest, QString data)
{
	if (sockDest != m_sockDesc) return;
	if (data.isEmpty()) {return;}
	qDebug() << sockDest << " " << data;
	socket->sendMessage(data);
}

void ServerThread::clientWaitForGame(QString account, QString character)
{
	emit threadWaitForGame(account, character);
}

void ServerThread::gameStart(QString enemyAccount, QString enemyCharacter)
{
	socket->gameStart(enemyAccount, enemyCharacter);
}

void ServerThread::gameData(QString data)
{
	//emit threadGameData(data);
	enemy->sendMessage(enemy->m_sockDesc ,data);
	sendMessage(m_sockDesc, data);
}

void ServerThread::disconnectToHost()
{
	socket->disconnectFromHost();
	emit disconnectTCP(m_sockDesc);
}