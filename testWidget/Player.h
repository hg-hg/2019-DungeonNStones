#pragma once

#include <QWidget>
#include "Character.h"
#include "SkillManager.h"
#include "ui_player.h"
class Player : public QWidget
{
	Q_OBJECT

public slots:
	void skillInvoke(QString skill, int cost);
	void stoneCrush(int hp, int damage, int mp, QString account);
	void receiveInfo(QString account, int hp, int damage, int mp);
	void initialStatus();
signals:
	void sendInfo(QString account, int hp, int damage, int mp);
	void dead(QString account);
	void useSkill(QString skillName, QString account);
public:
	Player(QWidget* parent);
	void setAccount(QString ACCOUNT);
	Player(QWidget *parent, QString ACCOUNT);
	void setCharacter(Character* ch);
	void setAsEnemy();
	void takeDamage(int);
	void recoverHP(int);
	void recoverMP(int);
	~Player();

private:
	Ui::PlayerWidget ui;
	Character* character;
	QString account = "NULL";
	SkillManager* sm = new SkillManager(this);
	int hp = 0, mp = 0;
	int maxHP, maxMP;
	bool enemy = false;
};
