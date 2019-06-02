#include "stdafx.h"
#include "AccountManager.h"
#include "const.h"

AccountManager::AccountManager(QObject *parent)
	: QObject(parent)
{
}

AccountManager::~AccountManager()
{
}

QString AccountManager::getAccount(QString accountName)
{
	auto fileName = "./account/" + accountName + ".txt";
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		qDebug(); return false;
	}
	QTextStream in(&file);
	QString name, character;
	int money;
	name = in.readLine();
	money = in.readLine().toInt();
	//current = new Account(this, cm);
	QString message = QString::number(MessageType::RequestAccount) + "\n";
	message.append(name + "\n" + QString::number(money) + "\n");
	character = in.readLine();
	message.append(character + "\n");
	QStringList list;
	while (!in.atEnd()) {
		character = in.readLine();
		list.append(character);
	}
	message.append(QString::number(list.size()) + "\n");
	for (auto str : list) message.append(str + "\n");
	
	return message;
}

void AccountManager::setAccount(QString accountName, QString str)
{
	auto fileName = "./account/" + accountName + ".txt";
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		qDebug(); return;
	}
	QTextStream out(&file);
	if (str[str.size() - 1] == "\n") str.chop(1);
	out << accountName << "\n" << str;
}

