#include "stdafx.h"
#include "Account.h"
#include "Client.h"

Account* Account::instance = nullptr;

Account* Account::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Account();
		atexit(release);
	}
	return instance;
}

Account::Account(QObject* parent)
{
}

void Account::release()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
}

Account::~Account()
{
}

bool Account::hasBoughtCharacter(const QString characterName) const
{
	return characters.contains(characterName);
}

bool Account::buyCharacter(const QString characterName, const int cost)
{
	if (hasBoughtCharacter(characterName)) return false;
	if (money < cost) return false;
	money -= cost;
	characters.append(characterName);
	return true;
}

bool Account::setCharacter(const QString characterName)
{
	if (!hasBoughtCharacter(characterName)) return false;
	selectedCharacter = cm->getCharacter(characterName);
	return true;
}

Character* Account::getSelectedCharacter() const
{
	return selectedCharacter;
}

void Account::sendAccountInfo() const
{
	QStringList list;
	list.append(name);
	list.append(QString::number(money));
	list.append(selectedCharacter->name);
	list.append(QString::number(characters.size()));
	for (auto c : characters) list.append(c);
	Client::getInstance()->sendAccountInfo(list);
}

void Account::addMoney(const int gain)
{
	money += gain;
}
