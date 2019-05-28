#pragma once

#include <QObject>
#include "Character.h"
class CharacterManager : public QObject
{
	Q_OBJECT
public:
	static CharacterManager* getInstance();
	static void release();
	Character* getCharacter(QString name) const;
	QMap<QString, Character*> characters;
private:
	static CharacterManager* instance;
	CharacterManager(QObject *parent = Q_NULLPTR);
	CharacterManager(const CharacterManager &);
	CharacterManager& operator=(const CharacterManager &);
	~CharacterManager();
	
private:
	void readCharacter(QFile& file);
	void initialize();
};
