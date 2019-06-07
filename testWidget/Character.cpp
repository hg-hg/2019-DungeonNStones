#include "stdafx.h"
#include "Character.h"

Character::Character(QObject* parent)
	:QObject(parent)
{
}

Character::Character(QObject* parent, const QString Name, const QString desc, const int Price, const int HP, const int MP, const QString Skin)
	: QObject(parent), name(Name), description(desc), price(Price), hp(HP), mp(MP), skin(Skin)
{
}

void Character::operator=(const Character& character)
{
	name = character.name;
	description = character.description;
	price = character.price;
	hp = character.hp;
	mp = character.mp;
	skin = character.skin;
	skills = character.skills;
}

void Character::setData(const Character* character)
{
	name = character->name;
	description = character->description;
	price = character->price;
	hp = character->hp;
	mp = character->mp;
	skin = character->skin;
	skills = character->skills;
}

Character::~Character()
{
}
