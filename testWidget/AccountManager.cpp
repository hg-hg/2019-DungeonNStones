#include "stdafx.h"
#include "AccountManager.h"

AccountManager::AccountManager(QObject* parent)
	: QObject(parent)
{
}

AccountManager::~AccountManager()
{
}

bool AccountManager::setCurrentAccount(const QString accountName)
{
	const auto fileName = "./Account/" + accountName + ".txt";
	QFile file(fileName);
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		createNewAccount(accountName);
		setCurrentAccount(accountName);
		return false;
	}
	QTextStream in(&file);
	const auto name = in.readLine();
	const auto money = in.readLine().toInt();
	//current = new Account(this, cm);

	current->name = name;
	current->money = money;
	auto character = in.readLine();
	current->selectedCharacter = cm->getCharacter(character);
	while (!in.atEnd())
	{
		character = in.readLine();
		current->characters.append(character);
	}
	return true;
}

bool AccountManager::setCurrentAccount(const QString name, const int money, const QString defaultCharacter)
{
	current->name = name;
	current->money = money;
	current->selectedCharacter = cm->getCharacter(defaultCharacter);
	return false;
}

Account* AccountManager::getCurrentAccount() const
{
	return current;
}

void AccountManager::createNewAccount(const QString accountName)
{
	const auto fileName = "./account/" + accountName + ".txt";
	QFile file(fileName);
	file.open(QFile::WriteOnly | QFile::Text);
	QTextStream out(&file);
	const auto message = accountName + "\n0\nKnight\nKnight";
	out << message;
}

void AccountManager::setAccount()
{
	Account * account = Account::getInstance();
	auto fileName = "./account/" + account->name + ".txt";
	QFile file(fileName);
	if (!file.open(QFile::WriteOnly | QFile::Text)) {
		qDebug(); return;
	}
	QTextStream out(&file);
	auto info = account->name + "\n" + QString::number(account->money) + "\n" + account->selectedCharacter->name;
	for (auto c : account->characters) info += "\n" + c;
	out << info;
}
