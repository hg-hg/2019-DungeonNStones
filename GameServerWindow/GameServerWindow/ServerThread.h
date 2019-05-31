#pragma once

#include <QThread>
#include "MySocket.h"

class ServerThread : public QThread
{
	Q_OBJECT
public:
	ServerThread(int sockDesc, QObject *parent = Q_NULLPTR);
	~ServerThread();

private:
	void run();

public slots:
	void sendMessage(int sockDest, QString data);

signals:
	//void dataReady(const QString &data);
	//void sendMessage(const QString &data);
	void disconnectTCP(int sockDesc);
	void threadWaitForGame(QString account, QString character);
	void threadGameData(QString data);

private slots:
	void disconnectToHost();
	void clientWaitForGame(QString account, QString character);
	void gameStart(QString enemyAccount, QString enemyCharacter);
	void gameData(QString data);
	//void addAccount(QString account);
	//void readMessage(const QString &data);

public:
	MySocket * socket;
	int m_sockDesc;
};
