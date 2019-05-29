#pragma once

#include <QTcpSocket>
#include "const.h"

class Client : public QTcpSocket
{
	Q_OBJECT

private:
	Client(QObject *parent = Q_NULLPTR);
	Client(const Client &);
	Client& operator=(const Client &);
	static Client* instance;

public:
	static Client* getInstance();
	static void release();
	void connectToServer();
	~Client();

public slots:
	void readMessage();
	void sendMessage(QString message);
	void requestAccount();
	void gameStart();
	void sendGameData(QString account, int hp, int damage, int mp);
	void sendWaitForGame(QString account, QString character);
	void sendDead(QString account);
	void sendBuyCharacter(QString account, QString character);

signals:
	void gameData(QString account, int hp, int damage, int mp);
	void gameStart(QString enemyAccount, QString enemyCharacter);

};
