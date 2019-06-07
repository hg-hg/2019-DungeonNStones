#pragma once

#include <QObject>

class Character : public QObject
{
Q_OBJECT

public:
	explicit Character(QObject* parent = Q_NULLPTR);
	Character(QObject* parent, QString Name, QString desc, int Price, int HP, int MP, QString Skin);
	void operator=(const Character& character);
	void setData(const Character* character);
	~Character();

	QString name;
	QString description;
	int price;
	int hp;
	int mp;
	QString skin;
	QList<QString> skills;
};
