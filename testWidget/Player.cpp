#include "stdafx.h"
#include "Player.h"

void Player::stoneCrush(const int hp, const int damage, const int mp, const QString& account)
{
	if (this->account == account)
	emit sendInfo(account, hp, damage, mp);
}

void Player::receiveInfo(const QString& account, const int hp, const int damage, const int mp)
{
	if (hp == 0) return;
	if (account != this->account) takeDamage(damage);
	else
	{
		recoverHP(hp);
		recoverMP(mp);
	}
}

void Player::initialStatus()
{
	hp = maxHP = character->hp;
	maxMP = character->mp;
	mp = 0;
	ui.HP->setMaximum(maxHP);
	ui.HP->setValue(hp);
	ui.MP->setMaximum(maxMP);
	ui.MP->setValue(mp);
	setGamePause(false);
}

Player::Player(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	//QFont font = QFont("·½Õý»ù´¡ÏñËØ");
	//ui.HP->setFont(font);
}

void Player::setAccount(const QString account)
{
	this->account = account;
}

void Player::skillInvoke(const QString& skill, const int cost)
{
	if (hp == 0) return;
	if (gamePause) return;
	if (mp < cost) return;
	emit useSkill(skill, account);
	emit sendInfo(account, 0, 0, -cost);
}

void Player::setCharacter(Character* ch)
{
	character = ch;
	initialStatus();
	for (const auto& name : character->skills)
	{
		auto c = sm->getSkill(name, ui.verticalLayoutWidget);
		if (enemy) c->setEnabled(false);
		connect(c, SIGNAL(useSkill(QString, int)), this, SLOT(skillInvoke(QString, int)));
		connect(this, SIGNAL(pauseGame()), c, SLOT(frozeTimer()));
		connect(this, SIGNAL(restartGame()), c, SLOT(restartTimer()));
		ui.skills->addWidget(c);
	}
	const auto skinPath = "./skin/" + character->skin;
	if (character->skin.endsWith(".gif"))
	{
		auto skin = new QMovie(skinPath);

		auto skinSize = QSize(320, 560);
		//QSize skinSize = skin->currentImage().size();
		//skin = skin->scaledSize(skinSize);
		auto he = skinSize.height();
		auto wi = skinSize.width();
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

void Player::takeDamage(const int damage)
{
	if (hp == 0) return;
	if (hp > damage) hp -= damage;
	else
	{
		hp = 0;
		emit dead(account);
	}
	ui.HP->setValue(hp);
}

void Player::recoverHP(const int HP)
{
	hp += HP;
	hp = qMin(hp, character->hp);
	ui.HP->setValue(hp);
}

void Player::recoverMP(const int MP)
{
	mp += MP;
	mp = qMin(mp, character->mp);
	ui.MP->setValue(mp);
}

void Player::setGamePause(const bool pause)
{
	gamePause = pause;
	if (pause) emit pauseGame();
	else emit restartGame();
}

Player::~Player()= default;
