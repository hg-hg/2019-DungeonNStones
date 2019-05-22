#pragma once

#include <QObject>
#include "Account.h"
#include "CharacterManager.h"
class AccountManager : public QObject
{
	Q_OBJECT

public:
	AccountManager(QObject *parent, CharacterManager* chaMa);
	~AccountManager();
	bool setCurrentAccount(QString accountName);
	Account* getCurrentAccount() const;
private:
	Account* current;
	CharacterManager* cm;
};
