#include "stdafx.h"
#include "Account.h"
#include "Client.h"

//Account::Account(QObject *parent, CharacterManager* chaMa)
//	: QObject(parent), cm(chaMa)
//{
//}

Account* Account::instance = nullptr;

Account* Account::getInstance() {
	if (instance == nullptr) {
		instance = new Account();
		atexit(release);
	}
	return instance;
}

Account::Account(QObject * parent)
{
}

void Account::release()
{
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}

Account::~Account()
{
}

bool Account::hasBoughtCharacter(QString chaName) const
{
	return characters.contains(chaName);
}

bool Account::buyCharacter(QString chaName, int cost)
{
	if (hasBoughtCharacter(chaName)) return false;
	if (money < cost) return false;
	money -= cost;
	characters.append(chaName);
	Client::getInstance()->sendBuyCharacter(name, chaName);
	return true;
}

bool Account::setCharacter(QString chaName)
{
	if (!hasBoughtCharacter(chaName)) return false;
	selectedCharacter = cm->getCharacter(chaName);
	return true;
}

Character * Account::getSelectedCharacter() const
{
	return selectedCharacter;
}

