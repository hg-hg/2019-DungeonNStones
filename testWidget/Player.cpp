#include "stdafx.h"
#include "Player.h"

void Player::stoneCrush(int hp, int damage, int mp)
{
	emit sendInfo(account, hp, damage, mp);
}

void Player::receiveInfo(QString account, int hp, int damage, int mp)
{
	if (account != this->account) takeDamage(damage);
	else {
		recoverHP(hp);
		recoverMP(mp);
	}
}

Player::Player(QWidget * parent)
	:QWidget(parent)
{
	ui.setupUi(this);
}

void Player::setAccount(QString ACCOUNT)
{
	account = ACCOUNT;
}

Player::Player(QWidget * parent, QString ACCOUNT)
	:QWidget(parent), account(ACCOUNT)
{
	ui.setupUi(this);
}

void Player::skillInvoke(QString skill, int cost) {
	if (mp < cost) return;
	mp -= cost;
	ui.MP->setValue(mp);
	emit useSkill(skill);
}

void Player::setCharacter(Character* ch)
{
	character = ch;
	character->setParent(this);
	hp = maxHP = character->hp;
	maxMP = character->mp;
	mp = 0;
	ui.HP->setMaximum(maxHP);
	ui.HP->setValue(hp);
	ui.MP->setMaximum(maxMP);
	ui.MP->setValue(mp);
	for (auto name : character->skills) {
		auto c = sm->getSkill(name, ui.verticalLayoutWidget);
		if (enemy) c->setEnabled(false);
		else {
			connect(c, SIGNAL(useSkill(QString, int)), this, SLOT(skillInvoke(QString, int)));
		}
		ui.skills->addWidget(c);
	}
	auto skinPath = "./skin/" + character->skin;
	QPixmap skin(skinPath);
	skin = skin.scaled(ui.characterInfo->size(), Qt::KeepAspectRatio);
	ui.characterInfo->setPixmap(skin);
}

void Player::setAsEnemy()
{
	enemy = true;
}

void Player::takeDamage(int damage)
{
	if (hp > damage) hp -= damage;
	else {
		hp = 0;
		emit dead(account);
	}
	ui.HP->setValue(hp);
}

void Player::recoverHP(int HP)
{
	hp += HP;
	hp = qMin(hp, character->hp);
	ui.HP->setValue(hp);
}

void Player::recoverMP(int MP)
{
	mp += MP;
	mp = qMin(mp, character->mp);
	ui.MP->setValue(mp);
}

Player::~Player()
{
}