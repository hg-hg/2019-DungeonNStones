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
		qDebug();
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
