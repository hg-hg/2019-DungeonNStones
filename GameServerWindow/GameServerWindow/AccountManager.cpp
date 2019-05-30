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
	auto fileName = "./Account/" + accountName + ".txt";
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

