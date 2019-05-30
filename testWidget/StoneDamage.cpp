#include "stdafx.h"
#include "StoneDamage.h"

StoneDamage::StoneDamage(QWidget *parent)
	: Stone(parent)
{
	setData();
	setImage();
}


void StoneDamage::setData()
{
	TYPE = DAMAGE_STONE;
	HP = 0;
	DAMAGE = 10;
	MP = 0;
}

void StoneDamage::setImage()
{
	//background = Qt::lightGray;
	background = QPixmap("./Resources/stone_background.png");
	foreground = QPixmap(":/foreground/Resources/foreground/damage.png");
}
