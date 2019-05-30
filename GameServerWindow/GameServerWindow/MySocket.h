#pragma once

#include <QTcpSocket>
#include "const.h"

class MySocket : public QTcpSocket
{
	Q_OBJECT
public:
	explicit MySocket(int sockDesc, QObject *parent = Q_NULLPTR);
	~MySocket();

private:
	QString getLine();
	void accountInfo();
	void clientWaitForGame();
	void receiveGameData();
public:
	void gameStart(QString enemyAccount, QString enemyCharacter);

signals:
	void waitForGame(QString account, QString character);
	void clientGameData(QString data);
	//void dataReady(const QString &data);
//void addAccount(QString account);

public slots:
	void readMessage();
	void sendMessage(QString data);
	
	

public:
	QString account;
private:
	int m_sockDesc;
};
