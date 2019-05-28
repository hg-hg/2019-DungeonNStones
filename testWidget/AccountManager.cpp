#include "stdafx.h"
#include "AccountManager.h"

AccountManager::AccountManager(QObject *parent)
	: QObject(parent)
{
}

AccountManager::~AccountManager()
{
}

bool AccountManager::setCurrentAccount(QString accountName)
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
	
	current->name = name;
	current->money = money;
	character = in.readLine();
	current->selectedCharacter = cm->getCharacter(character);
	while (!in.atEnd()) {
		character = in.readLine();
		current->characters.append(character);
	}
	return true;
}

Account * AccountManager::getCurrentAccount() const
{
	return current;
}
