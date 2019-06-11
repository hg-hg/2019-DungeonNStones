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
	void die();
	QString getLine(int times = 0);

public:
	static Client* getInstance();
	static void release();
	bool connectToServer();
	void sendMessage(const QString& message);
	void requestAccount(const QString& accountName);
	void sendWaitForGame(const QString& account, const QString& character);
	void sendDisconnecting();
	void sendAccountInfo(const QStringList& info);
	void sendStopMatching();
	void sendEscapeGame();
	void sendDead(const QString& account);
	~Client();

public slots:
	void readMessage();
	void sendGameData(const QString& account, int hp, int damage, int mp);
	
	void gameData();

signals:
	void accountInitialized();
	void gameData(QString account, int hp, int damage, int mp);
	void gameStart(QString enemyAccount, QString enemyCharacter);
	void enemyDisconnect();
	void dead(QString account);

public:
	bool online;
};
