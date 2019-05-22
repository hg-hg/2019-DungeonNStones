#include "stdafx.h"
#include "Character.h"

Character::Character(QObject *parent, QString Name, QString desc, int Price, int HP, int MP, QString Skin)
	: QObject(parent), name(Name), description(desc), price(Price), hp(HP), mp(MP), skin(Skin)
{
}

void Character::operator=(const Character & character)
{
	name = character.name;
	description = character.description;
	price = character.price;
	hp = character.hp;
	mp = character.mp;
	skin = character.skin;
	skills = character.skills;
}

Character::~Character()
{
}
