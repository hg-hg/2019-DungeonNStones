#pragma once

#include <QObject>
#include "Skill.h"
class Character : public QObject
{
	Q_OBJECT

public:
	Character(QObject *parent, QString Name, QString desc, int Price, int HP, int MP, QString Skin);
	void operator= (const Character& character);
	~Character();

	QString name;
	QString description;
	int price;
	int hp;
	int mp;
	QString skin;
	QList<QString> skills;
};
