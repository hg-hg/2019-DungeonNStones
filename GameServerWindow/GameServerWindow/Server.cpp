#include "stdafx.h"
#include "Server.h"

Server::Server(QObject *parent) :
	QTcpServer(parent)
{
	/* get current dialog object */
	//m_dialog = dynamic_cast<Dialog *>(parent);
}

Server::~Server()
{

}

void Server::incomingConnection(qintptr sockDesc)
{

	ServerThread *thread = new ServerThread(sockDesc);
	//QMessageBox::information(NULL, "amd yes", "coming");
	emit changeUI("thread coming, socket desc: " + QString::number(sockDesc));
	//m_dialog->showConnection(sockDesc);

	connect(thread, SIGNAL(disconnectTCP(int)), this, SLOT(clientDisconnected(int)));
	//connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	connect(thread, SIGNAL(finished()), this, SLOT(deleteLater()));
	//connect(thread, SIGNAL(addAccount(QString)), this, SLOT(addAccount(QString)));
	connect(thread, SIGNAL(threadWaitForGame(QString, QString)), this, SLOT(waitingForGame(QString, QString)));
	connect(this, SIGNAL(sendMessage(int, QString)), thread, SLOT(sendMessage(int, QString)));
	connect(thread, SIGNAL(threadGameData(QString)), this, SLOT(sendGameData(QString)));
	//connect(thread, SIGNAL(dataReady(QString)))
	
	online.append(thread);


	thread->start();
}

void Server::waitingForGame(QString account, QString character)
{
	auto thread = static_cast<ServerThread*>(sender());

	if (waiting.empty()) {
		waiting.append(qMakePair(character, thread));
	}
	else {
		int sockDesc = thread->m_sockDesc;
		auto pair = waiting.front();
		auto enemyCharacter = pair.first;
		auto enemyThread = pair.second;
		int enemySockDesc = enemyThread->m_sockDesc;
		QString enemyAccount = enemyThread->socket->account;
		waiting.pop_front();
		QString base = QString::number(MessageType::GameStart) + "\n";
		QString enemy = base + enemyAccount + "\n" + enemyCharacter;
		base += account + "\n" + character;
		emit sendMessage(sockDesc, enemy);
		emit sendMessage(enemySockDesc, base);
		playing.append(qMakePair(thread, enemyThread));
	}
}

void Server::sendGameData(QString data)
{
	auto thread = static_cast<ServerThread*>(sender());
	for (auto p : playing) {
		if (p.first == thread || p.second == thread) {
			emit sendMessage(p.first->m_sockDesc, data);
			emit sendMessage(p.second->m_sockDesc, data);
			return;
		}
	}
}

void Server::clientDisconnected(int sockDesc)
{
	emit changeUI(QString::number(sockDesc) + " disconnect");
	auto thread = static_cast<ServerThread*>(sender());
	QString message = QString::number(MessageType::Disconnect);
	for (auto it = playing.begin(); it != playing.end();) {
		if (it->first == thread) {
			emit sendMessage(it->second->m_sockDesc, message);
			it = playing.erase(it);
		}
		else if (it->second == thread) {
			emit sendMessage(it->first->m_sockDesc, message);
			it = playing.erase(it);
		}
		else it++;
	}
	for (auto it = online.begin(); it != online.end(); ) {
		if (*it == thread) {
			it = online.erase(it);
			break;
		}
		else it++;
	}
	thread->deleteLater();
}
