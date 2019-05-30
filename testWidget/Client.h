#pragma once

#include <QTcpSocket>
#include "const.h"
#include "AccountManager.h"

class Client : public QTcpSocket
{
	Q_OBJECT

private:
	Client(QObject *parent = Q_NULLPTR);
	Client(const Client &);
	Client& operator=(const Client &);
	static Client* instance;
	AccountManager* am = new AccountManager();
	void initializeAccount();
	QString getLine();
public:
	static Client* getInstance();
	static void release();
	void connectToServer();
	~Client();

public slots:
	void readMessage();
	void sendMessage(const QString& message);
	void requestAccount(QString accountName);
	void gameStart();
	void sendGameData(QString account, int hp, int damage, int mp);
	void sendWaitForGame(QString account, QString character);
	void sendDead(QString account);
	void sendBuyCharacter(QString account, QString character);
	void gameData();

signals:
	void gameData(QString account, int hp, int damage, int mp);
	void gameStart(QString enemyAccount, QString enemyCharacter);

};
