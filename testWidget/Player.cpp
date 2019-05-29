#include "stdafx.h"
#include "Player.h"

void Player::stoneCrush(int hp, int damage, int mp, QString account)
{
	if (this->account == account)
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
	emit useSkill(skill, account);
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
		connect(c, SIGNAL(useSkill(QString, int)), this, SLOT(skillInvoke(QString, int)));
		
		ui.skills->addWidget(c);
	}
	auto skinPath = "./skin/" + character->skin;
	if (character->skin.endsWith(".gif"))
	{
		QMovie *skin = new QMovie(skinPath);

		QSize skinSize = QSize(320, 560);
		//QSize skinSize = skin->currentImage().size();
		//skin = skin->scaledSize(skinSize);
		int he = skinSize.height();
		int wi = skinSize.width();
		if (wi > ui.characterInfo->size().width())
		{
			he *= ui.characterInfo->size().width();
			he /= wi;
			wi = ui.characterInfo->size().width();
		}
		if (he > ui.characterInfo->size().height())
		{
			wi *= ui.characterInfo->size().height();
			wi /= he;
			he = ui.characterInfo->size().height();
		}
		skinSize.setHeight(he);
		skinSize.setWidth(wi);
		skin->setScaledSize(skinSize);
		//skin->setScaledSize(ui.characterInfo->size());
		ui.characterInfo->setMovie(skin);
		skin->start();
	}
	else
	{
		QPixmap skin(skinPath);
		skin = skin.scaled(ui.characterInfo->size(), Qt::KeepAspectRatio);
		ui.characterInfo->setPixmap(skin);
	}
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
