#pragma once

#include <QObject>
#include "CharacterManager.h"
#include "Account.h"

class AccountManager : public QObject
{
	Q_OBJECT

public:
	AccountManager(QObject *parent = Q_NULLPTR);
	~AccountManager();
	bool setCurrentAccount(QString accountName);
	bool setCurrentAccount(QString name, int money, QString defaultCharacter);
	Account* getCurrentAccount() const;
private:
	Account* current = Account::getInstance();
	CharacterManager* cm = CharacterManager::getInstance();
};
