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
	QString getLine(int times = 0);
	void accountInfo();
	void clientWaitForGame();
	void receiveGameData();
	void accountChanged();
public:
	void gameStart(QString enemyAccount, QString enemyCharacter);

signals:
	void waitForGame(QString account, QString character);
	void clientGameData(QString data);

public slots:
	void readMessage();
	void sendMessage(QString data);
	
	

public:
	QString account;
private:
	int m_sockDesc;
};
