#pragma once

#include <QObject>
#include "CharacterManager.h"

class Account : public QObject
{
	Q_OBJECT
friend class AccountManager;
friend class GameBoard;
public:
	Account(QObject *parent, CharacterManager* chaMa);
	~Account();
	bool hasBoughtCharacter(QString chaName) const;
	bool buyCharacter(QString chaName, int cost);
	bool setCharacter(QString chaName);
	Character* getSelectedCharacter() const;
private:
	QString name;
	int money;
	QList<QString> characters;
	Character* selectedCharacter;
	CharacterManager* cm;
};
