#include "stdafx.h"
#include "Client.h"
#include <QHostAddress>

Client* Client::instance = nullptr;

Client::Client(QObject* parent)
	: QTcpSocket(parent)
{
	//connectToServer();
}

void Client::initializeAccount()
{
	const auto name = getLine();
	const auto money = getLine().toInt();
	auto character = getLine();
	const auto size = getLine().toInt();
	am->setCurrentAccount(name, money, character);
	for (auto i = 0; i < size; i++)
	{
		character = getLine();
		Account::getInstance()->characters.append(character);
	}
	emit accountInitialized();
}

QString Client::getLine(int times)
{
	const QString str = readLine();
	if (str.isEmpty() && times < 10) return getLine(++times);
	return str.simplified();
}

Client* Client::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Client();
		atexit(release);
	}
	return instance;
}

void Client::release()
{
	if (instance)
	{
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
	const auto message = QString::number(Disconnect);
	sendMessage(message);
	disconnectFromHost();
}

void Client::sendAccountInfo(QStringList info)
{
	auto message = QString::number(AccountChange) + "\n";
	for (auto str : info) message += str + "\n";
	sendMessage(message);
}

void Client::sendStopMatching()
{
	const auto message = QString::number(StopMatching) + "\n";
	sendMessage(message);
}

void Client::sendEscapeGame()
{
	const auto message = QString::number(EscapeGame) + "\n";
	sendMessage(message);
}

Client::~Client()
{
}

void Client::readMessage()
{
	const auto type = static_cast<MessageType>(getLine().toInt());
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
	case EscapeGame:
		emit enemyDisconnect();
		break;
	default: ;
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
	const auto message = QString::number(RequestAccount) + "\n" + accountName;
	sendMessage(message);
	waitForReadyRead();
}

void Client::gameStart()
{
	const auto enemyAccount = getLine();
	const auto enemyCharacter = getLine();
	//qDebug() << enemyAccount << enemyCharacter;
	emit gameStart(enemyAccount, enemyCharacter);
}

void Client::sendGameData(const QString account, const int hp, const int damage, const int mp)
{
	const auto message = QString::number(GameData) + "\n" +
		account + "\n" + QString::number(hp) + "\n" + QString::number(damage) + "\n" + QString::number(mp) + "\n";
	sendMessage(message);
}

void Client::sendWaitForGame(const QString account, const QString character)
{
	const auto message = QString::number(WaitForGame) + "\n" + account + "\n" + character + "\n";
	sendMessage(message);
	//waitForReadyRead();
}

void Client::sendDead(const QString account)
{
	const auto message = QString::number(Dead) + "\n" + account + "\n";
	sendMessage(message);
}

void Client::gameData()
{
	const auto account = getLine();
	const auto hp = getLine().toInt();
	const auto damage = getLine().toInt();
	const auto mp = getLine().toInt();
	emit gameData(account, hp, damage, mp);
}
