#include "stdafx.h"
#include "StoneManager.h"
#include "StoneHP.h"
#include "StoneDamage.h"
#include "StoneMP.h"
#include "StoneHD.h"
#include "StoneHM.h"
#include "StoneDM.h"

StoneManager::StoneManager(QObject *parent)
	:QObject(parent)
{
	QTime t = QTime::currentTime();
	qsrand(t.msec() + t.second() * 1000);
}

StoneManager::StoneManager(QObject *parent, uint seed)
	:QObject(parent)
{
	StoneManager::StoneManager(parent);
	qsrand(seed);
}

Stone * StoneManager::getStone(int type, QWidget* parent)
{
	Stone * stone;
	switch (type)
	{
	case HP_STONE:
		stone = new StoneHP(parent);
		break;
	case DAMAGE_STONE:
		stone = new StoneDamage(parent);
		break;
	case MP_STONE:
		stone = new StoneMP(parent);
		break;
	case HD_STONE:
		stone = new StoneHD(parent);
		break;
	case HM_STONE:
		stone = new StoneHM(parent);
		break;
	case DM_STONE:
		stone = new StoneDM(parent);
		break;
	default:
		stone = new Stone(parent);
	}
	connect(stone, SIGNAL(clicked(Stone*)), parent, SLOT(clickedStone(Stone*)));
	return stone;
}

Stone * StoneManager::getStone(QWidget* parent)
{
	//I mod 7 because there are 7 types of stones
	int type = qrand() % 7;
	return getStone(type, parent);
}

void StoneManager::changeStone(Stone *& source, int dest, QWidget* parent)
{
	if (source->TYPE == dest) return;
	auto stone = getStone(dest, parent);
	source->TYPE = stone->TYPE;
	source->HP = stone->HP;
	source->DAMAGE = stone->DAMAGE;
	source->MP = stone->MP;
	source->foreground = stone->foreground;
	source->background = stone->background;
	source->repaint();
	delete stone;
}
