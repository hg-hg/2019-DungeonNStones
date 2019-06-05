#pragma once

#include <QWidget>
#include "Character.h"
#include "SkillManager.h"
#include "ui_player.h"

class Player : public QWidget
{
Q_OBJECT

public slots:
	void skillInvoke(const QString& skill, int cost);
	void stoneCrush(int hp, int damage, int mp, const QString& account);
	void receiveInfo(const QString& account, int hp, int damage, int mp);
	void initialStatus();
signals:
	void sendInfo(QString account, int hp, int damage, int mp);
	void dead(QString account);
	void useSkill(QString skillName, QString account);
	void pauseGame();
	void restartGame();
public:
	Player(QWidget* parent);
	void setAccount(QString account);
	void setCharacter(Character* ch);
	void setAsEnemy();
	void takeDamage(int);
	void recoverHP(int);
	void recoverMP(int);
	void setGamePause(bool pause);
	~Player();

private:
	Ui::PlayerWidget ui;
	Character* character;
	QString account = "NULL";
	SkillManager* sm = new SkillManager(this);
	int hp = 0, mp = 0;
	int maxHP, maxMP;
	bool enemy = false;
	bool gamePause = false;
};
