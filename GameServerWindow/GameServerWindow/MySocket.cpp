#include "stdafx.h"
#include "MySocket.h"
#include "AccountManager.h"
#include <QHostAddress>

MySocket::MySocket(const int sockDesc, QObject* parent) :
	QTcpSocket(parent), m_sockDesc(sockDesc)
{
	connect(this, SIGNAL(readyRead()), this, SLOT(readMessage()));
}

MySocket::~MySocket()
{
}

QString MySocket::getLine(int times)
{
	const QString str = readLine();
	if (str.isEmpty() && times < 10) return getLine(++times);
	return str.simplified();
}

void MySocket::sendMessage(const QString& data)
{
	if (!data.isEmpty())
	{
		write(data.toStdString().data());
	}
	waitForBytesWritten();
}

void MySocket::receiveGameData()
{
	QString message = QString::number(GameData) + "\n";
	//QString account, hp, damage, mp;
	//account = getLine();
	//hp = getLine();
	//damage = getLine();
	//mp = getLine();
	////readAll();
	//message += account + "\n" + hp + "\n" + damage + "\n" + mp + "\n";
	message += readAll();
	emit clientGameData(message);
}

void MySocket::accountChanged()
{
	AccountManager am;
	const auto account = getLine();
	const auto money = getLine();
	const auto selectedCharacter = getLine();
	auto str = money + "\n" + selectedCharacter + "\n"; // account, money, selected
	const auto amount = getLine().toInt();
	for (auto i = 0; i < amount; i++) str.append(getLine() + "\n");
	am.setAccount(account, str);
}

void MySocket::clientEscape()
{
	emit clientEscapeGame();
}

void MySocket::clientStopMatch()
{
	emit clientStopMatching();
}

void MySocket::clientDie()
{
	const auto account = getLine();
	emit clientDead(account);
}

void MySocket::accountInfo()
{
	AccountManager am;
	account = getLine();
	sendMessage(am.getAccount(account));
}

void MySocket::clientWaitForGame()
{
	const auto account = getLine();
	const auto character = getLine();
	emit waitForGame(account, character);
}

void MySocket::gameStart(const QString& enemyAccount, const QString& enemyCharacter)
{
	QString message = QString::number(GameStart) + "\n";
	message += enemyAccount + "\n" + enemyCharacter + "\n";
	sendMessage(message);
}

void MySocket::readMessage()
{
	const auto type = static_cast<MessageType>(getLine().toInt());
	switch (type)
	{
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
		clientDie();
		break;
	case Disconnect:
		break;
	case AccountChange:
		accountChanged();
		break;
	case EscapeGame:
		clientEscape();
		break;
	case StopMatching:
		clientStopMatch();
		break;
	default: ;
	}
}
