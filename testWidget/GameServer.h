#pragma once

#include <QObject>

class GameServer : public QObject
{
	Q_OBJECT

public:
	GameServer(QObject *parent);
	~GameServer();

public slots:
	void receiveInfo(QString account, int hp, int damage, int mp);

signals:
	void sendInfo(QString account, int hp, int damage, int mp);
};
