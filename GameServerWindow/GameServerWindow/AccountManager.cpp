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

QString AccountManager::getAccount(const QString accountName)
{
	const auto fileName = "./account/" + accountName + ".txt";
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		return QString::number(MessageType::RequestAccount) + "\n" + createNewAccount(accountName);
	}
	QTextStream in(&file);
	const auto name = in.readLine();
	const auto money = in.readLine().toInt();
	auto message = QString::number(MessageType::RequestAccount) + "\n";
	message.append(name + "\n" + QString::number(money) + "\n");
	auto character = in.readLine();
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

QString AccountManager::createNewAccount(const QString accountName)
{
	const auto fileName = "./account/" + accountName + ".txt";
	QFile file(fileName);
	file.open(QFile::WriteOnly | QFile::Text);
	QTextStream out(&file);
	auto message = accountName + "\n" + QString::number(0) + "\n" + "Knight" + "\n" + QString::number(1)+ "\n" +"Knight";
	out << message;
	return message;
}

void AccountManager::setAccount(const QString accountName, QString str)
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