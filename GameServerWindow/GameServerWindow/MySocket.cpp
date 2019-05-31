#include "stdafx.h"
#include "MySocket.h"
#include "AccountManager.h"
#include <QHostAddress>

MySocket::MySocket(int sockDesc, QObject *parent) :
	QTcpSocket(parent), m_sockDesc(sockDesc)
{
	connect(this, SIGNAL(readyRead()), this, SLOT(readMessage()));
}

MySocket::~MySocket()
{

}

QString MySocket::getLine()
{
	QString str = readLine();
	if (str.isEmpty()) return getLine();
	return str.simplified();
}

void MySocket::sendMessage(QString data)
{
	if (!data.isEmpty()) {
		write(data.toStdString().data());
	}
	waitForBytesWritten();
}

void MySocket::receiveGameData()
{
	QString message = QString::number(MessageType::GameData) + "\n";
	QString account, hp, damage, mp;
	account = getLine();
	hp = getLine();
	damage = getLine();
	mp = getLine();
	readAll();
	message += account + "\n" + hp + "\n" + damage + "\n" + mp;
	emit clientGameData(message);
}

void MySocket::accountInfo()
{
	AccountManager am;
	account = getLine();
	sendMessage(am.getAccount(account));
}

void MySocket::clientWaitForGame()
{
	QString account = getLine();
	QString character = getLine();
	emit waitForGame(account, character);
}

void MySocket::gameStart(QString enemyAccount, QString enemyCharacter)
{
	QString message = QString::number(MessageType::GameStart) + "\n";
	message += enemyAccount + "\n" + enemyCharacter + "\n";
	sendMessage(message);
}

void MySocket::readMessage()
{
	MessageType type = static_cast<MessageType>(getLine().toInt());
	switch (type) {
	case RequestAccount:
		accountInfo();
		break;
	case WaitForGame:
		clientWaitForGame();
		break;
	case GameData:
		receiveGameData();
		break;
	case Dead:
		
		break;
	case Disconnect:
		break;
	case BuyCharacter:
		break;
	}
}
