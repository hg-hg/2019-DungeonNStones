#pragma once

#include <QTcpSocket>
#include "const.h"
#include "AccountManager.h"

class Client : public QTcpSocket
{
Q_OBJECT

private:
	static Client* instance;
	Client(QObject* parent = Q_NULLPTR);
	Client(const Client&);
	Client& operator=(const Client&);

	AccountManager* am = new AccountManager();
	void initializeAccount();
	void gameStart();
	QString getLine(int times = 0);

public:
	static Client* getInstance();
	static void release();
	void connectToServer();
	void sendMessage(const QString& message);
	void requestAccount(QString accountName);
	void sendWaitForGame(QString account, QString character);
	void sendDisconnecting();
	void sendAccountInfo(QStringList info);
	void sendStopMatching();
	void sendEscapeGame();
	~Client();

public slots:
	void readMessage();
	void sendGameData(QString account, int hp, int damage, int mp);
	void sendDead(QString account);
	void gameData();

signals:
	void accountInitialized();
	void gameData(QString account, int hp, int damage, int mp);
	void gameStart(QString enemyAccount, QString enemyCharacter);
	void enemyDisconnect();
};
