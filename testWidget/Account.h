#pragma once

#include <QObject>
#include "CharacterManager.h"

class Account : public QObject
{
Q_OBJECT
public:
	static Account* getInstance();
	static void release();
	~Account();
	bool hasBoughtCharacter(QString characterName) const;
	bool buyCharacter(QString characterName, int cost);
	bool setCharacter(QString characterName);
	Character* getSelectedCharacter() const;
	void sendAccountInfo() const;
	void addMoney(int gain);
private:
	Account(QObject* parent = Q_NULLPTR);
	Account(const Account&);
	Account& operator=(const Account&);

public:
	QString name;
	int money;
	QList<QString> characters;
	Character* selectedCharacter = nullptr;
private:
	CharacterManager* cm = CharacterManager::getInstance();
	static Account* instance;
};
