#pragma once

#include <QTcpServer>
#include "ServerThread.h"

class Server : public QTcpServer
{
	Q_OBJECT
public:
	explicit Server(QObject *parent = Q_NULLPTR);
	~Server();

protected:
	void incomingConnection(qintptr sockDesc) override;

signals:
	void sendMessage(int sockDest, QString message);
	void changeUI(QString);

private slots:
	void clientDisconnected(int sockDesc);
	void waitingForGame(const QString& account, const QString& character);
	void sendGameData(const QString& data);
	void escape();
	void stopMatching();
	void die(const QString& account);

private:
	QList<ServerThread*> online;
	//QMap<QString, ServerThread*> threadMap;
	QList<QPair<QString, ServerThread*>> waiting;
	QList<QPair<ServerThread*, ServerThread*>> playing;
};
