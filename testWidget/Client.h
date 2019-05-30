#pragma once

#include <QTcpSocket>

class Client : public QTcpSocket
{
	Q_OBJECT

public:
	Client(QObject *parent = Q_NULLPTR);
	~Client();
	bool searchingGame;
	bool playingGame;
	QString account;
	QString enemyAccount;
};
