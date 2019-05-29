#include "stdafx.h"
#include "Client.h"
#include <QHostAddress>

Client* Client::instance = nullptr;

Client::Client(QObject *parent)
	: QTcpSocket(parent)
{
	//connectToServer();
}

Client * Client::getInstance()
{
	if (instance == nullptr) {
		instance = new Client();
		atexit(release);
	}
	return instance;
}

void Client::release()
{
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}

void Client::connectToServer()
{
	connectToHost(QHostAddress::LocalHost, 10086);
	connect(this, SIGNAL(readyRead()), this, SLOT(readMessage()));
}

Client::~Client()
{
}

void Client::readMessage() {
	MessageType type = static_cast<MessageType>(readLine().toInt());
	switch (type)
	{
	case GameStart:
		gameStart();
		break;
	case GameData:
		break;
	case Dead:
		break;
	case Disconnect:
		break;
	}
}

void Client::sendMessage(QString message)
{
	write(message.toStdString().data());
	waitForBytesWritten();
}

void Client::requestAccount()
{
	QString message = MessageType::RequestAccount;
	sendMessage(message);
}

void Client::gameStart()
{
	QString enemyAccount = readLine();
	QString enemyCharacter = readLine();
	emit gameStart(enemyAccount, enemyCharacter);
}

void Client::sendGameData(QString account, int hp, int damage, int mp)
{
	QString message = QString::number(MessageType::GameData) + "\n" +
		account + "\n" + QString::number(hp) + "\n" + QString::number(damage) + "\n" + QString::number(mp);
	sendMessage(message);
}

void Client::sendWaitForGame(QString account, QString character)
{
	QString message = QString::number(MessageType::WaitForGame) + "\n" + account + "\n" + character;
	sendMessage(message);
}

void Client::sendDead(QString account)
{
	QString message = QString::number(MessageType::Dead) + "\n" + account;
	sendMessage(message);
}

void Client::sendBuyCharacter(QString account, QString character)
{
	QString message = QString::number(MessageType::BuyCharacter) + "\n" + account + "\n" + character;
}
