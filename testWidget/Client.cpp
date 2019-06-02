#include "stdafx.h"
#include "Client.h"
#include <QHostAddress>

Client* Client::instance = nullptr;

Client::Client(QObject *parent)
	: QTcpSocket(parent)
{
	//connectToServer();
	
}

void Client::initializeAccount()
{
	QString name, character;
	int money, size;
	name = getLine();
	money = getLine().toInt();
	character = getLine();
	size = getLine().toInt();
	am->setCurrentAccount(name, money, character);
	for (int i = 0; i < size; i++) {
		character = getLine();
		Account::getInstance()->characters.append(character);
	}
	emit accountInitialized();
}

QString Client::getLine(int times)
{
	QString str = readLine();
	if (str.isEmpty() && times < 10) return getLine(++times);
	return str.simplified();
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
	connectToHost(QHostAddress("39.107.229.247"), 27015);
	//connectToHost(QHostAddress::LocalHost, 27015);
	waitForConnected();
	connect(this, SIGNAL(readyRead()), this, SLOT(readMessage()));
}

void Client::sendDisconnecting()
{
	QString message = QString::number(MessageType::Disconnect);
	sendMessage(message);
	disconnectFromHost();
}

void Client::sendAccountInfo(QStringList info)
{
	QString message = QString::number(MessageType::AccountChange) + "\n";
	for (auto str : info) message += str + "\n";
	sendMessage(message);
}

Client::~Client()
{
}

void Client::readMessage() {
	MessageType type = static_cast<MessageType>(getLine().toInt());
	switch (type)
	{
	case RequestAccount:
		initializeAccount();
		break;
	case GameStart:
		gameStart();
		break;
	case GameData:
		gameData();
		break;
	case Dead:
		break;
	case Disconnect:
		emit enemyDisconnect();
		break;
	}
}

void Client::sendMessage(const QString& message)
{
	write(message.toStdString().data());
	waitForBytesWritten();
	//waitForReadyRead();
}

void Client::requestAccount(QString accountName)
{
	QString message = QString::number(MessageType::RequestAccount) + "\n" + accountName;
	sendMessage(message);
	waitForReadyRead();
}

void Client::gameStart()
{
	QString enemyAccount = getLine();
	QString enemyCharacter = getLine();
	//qDebug() << enemyAccount << enemyCharacter;
	emit gameStart(enemyAccount, enemyCharacter);
}

void Client::sendGameData(QString account, int hp, int damage, int mp)
{
	QString message = QString::number(MessageType::GameData) + "\n" +
		account + "\n" + QString::number(hp) + "\n" + QString::number(damage) + "\n" + QString::number(mp) + "\n";
	sendMessage(message);
}

void Client::sendWaitForGame(QString account, QString character)
{
	QString message = QString::number(MessageType::WaitForGame) + "\n" + account + "\n" + character + "\n";
	sendMessage(message);
	//waitForReadyRead();
}

void Client::sendDead(QString account)
{
	QString message = QString::number(MessageType::Dead) + "\n" + account + "\n";
	sendMessage(message);
}

void Client::gameData()
{
	QString account;
	int hp, damage, mp;
	account = getLine();
	hp = getLine().toInt();
	damage = getLine().toInt();
	mp = getLine().toInt();
	emit gameData(account, hp, damage, mp);
}
