#pragma once

#include <QObject>
#include "Character.h"
class CharacterManager : public QObject
{
	Q_OBJECT
public:
	CharacterManager(QObject *parent);
	~CharacterManager();
	Character* getCharacter(QString name) const;

	QMap<QString, Character*> characters;
private:
	void readCharacter(QFile& file);
	void initialize();
};
