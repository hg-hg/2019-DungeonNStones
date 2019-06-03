#include "stdafx.h"
#include "Server.h"

Server::Server(QObject* parent) :
	QTcpServer(parent)
{
}

Server::~Server()
{
}

void Server::incomingConnection(const qintptr sockDesc)
{
	auto* thread = new ServerThread(sockDesc);
	//QMessageBox::information(NULL, "amd yes", "coming");
	emit changeUI("thread coming, socket desc: " + QString::number(sockDesc));
	//m_dialog->showConnection(sockDesc);

	connect(thread, SIGNAL(disconnectTCP(int)), this, SLOT(clientDisconnected(int)));
	connect(thread, SIGNAL(finished()), thread, SLOT(deleteLater()));
	//connect(thread, SIGNAL(finished()), this, SLOT(deleteLater()));
	//connect(thread, SIGNAL(addAccount(QString)), this, SLOT(addAccount(QString)));
	connect(thread, SIGNAL(threadWaitForGame(QString, QString)), this, SLOT(waitingForGame(QString, QString)));
	connect(this, SIGNAL(sendMessage(int, QString)), thread, SLOT(sendMessage(int, QString)));
	connect(thread, SIGNAL(threadGameData(QString)), this, SLOT(sendGameData(QString)));
	connect(thread, SIGNAL(clientEscape()), this, SLOT(escape()));
	connect(thread, SIGNAL(clientStopMatching()), this, SLOT(stopMatching()));
	connect(thread, SIGNAL(clientDead(QString)), this, SLOT(die(QString)));

	online.append(thread);


	thread->start();
}

void Server::waitingForGame(const QString& account, const QString& character)
{
	auto thread = dynamic_cast<ServerThread*>(sender());

	if (waiting.empty())
	{
		waiting.append(qMakePair(character, thread));
	}
	else
	{
		const auto sockDesc = thread->sockDesc;
		const auto pair = waiting.front();
		const auto enemyCharacter = pair.first;
		const auto enemyThread = pair.second;
		const auto enemySockDesc = enemyThread->sockDesc;
		const auto enemyAccount = enemyThread->socket->account;
		waiting.pop_front();
		auto base = QString::number(GameStart) + "\n";
		const auto enemy = base + enemyAccount + "\n" + enemyCharacter + "\n";
		base += account + "\n" + character + "\n";
		emit sendMessage(sockDesc, enemy);
		emit sendMessage(enemySockDesc, base);
		thread->enemy = enemyThread;
		enemyThread->enemy = thread;
		playing.append(qMakePair(thread, enemyThread));
	}
}

void Server::sendGameData(const QString& data)
{
	auto thread = dynamic_cast<ServerThread*>(sender());
	for (auto p : playing)
	{
		if (p.first == thread || p.second == thread)
		{
			emit sendMessage(p.first->sockDesc, data);
			emit sendMessage(p.second->sockDesc, data);
			return;
		}
	}
}

void Server::escape()
{
	auto thread = dynamic_cast<ServerThread*>(sender());
	emit changeUI(QString::number(thread->sockDesc) + " escape");
	const auto message = QString::number(EscapeGame);
	for (auto it = playing.begin(); it != playing.end();)
	{
		if (it->first == thread || it->second == thread)
		{
			if (it->first == thread) emit sendMessage(it->second->sockDesc, message);
			else emit sendMessage(it->first->sockDesc, message);
			it = playing.erase(it);
			break;
		}
		++it;
	}
}

void Server::stopMatching()
{
	auto thread = dynamic_cast<ServerThread*>(sender());
	emit changeUI(QString::number(thread->sockDesc) + " stop matching");
	for (auto it = waiting.begin(); it != waiting.end();)
	{
		if (it->second == thread)
		{
			it = waiting.erase(it);
			break;
		}
		++it;
	}
}

void Server::clientDisconnected(const int sockDesc)
{
	emit changeUI(QString::number(sockDesc) + " disconnect");
	auto thread = dynamic_cast<ServerThread*>(sender());
	const auto message = QString::number(Disconnect);
	for (auto it = playing.begin(); it != playing.end();)
	{
		if (it->first == thread || it->second == thread)
		{
			if (it->first == thread) emit sendMessage(it->second->sockDesc, message);
			else emit sendMessage(it->first->sockDesc, message);
			it = playing.erase(it);
			break;
		}
		++it;
	}
	for (auto it = waiting.begin(); it != waiting.end();)
	{
		if (it->second == thread)
		{
			it = waiting.erase(it);
			break;
		}
		++it;
	}
	for (auto it = online.begin(); it != online.end();)
	{
		if (*it == thread)
		{
			it = online.erase(it);
			break;
		}
		++it;
	}
	thread->deleteLater();
}

void Server::die(const QString& account)
{
	auto thread = dynamic_cast<ServerThread*>(sender());
	emit changeUI(QString::number(thread->sockDesc) + " dead");
	const auto message = QString::number(Dead) + "\n" + account + "\n";
	for (auto it = playing.begin(); it != playing.end();)
	{
		const auto first = it->first;
		const auto second = it->second;
		if (first == thread || second == thread)
		{
			emit sendMessage(first->sockDesc, message);
			emit sendMessage(second->sockDesc, message);
			it = playing.erase(it);
			break;
		}
		++it;
	}
}
