#include "stdafx.h"
#include "StoneHP.h"

StoneHP::StoneHP(QWidget *parent)
	: Stone(parent)
{
	setData();
	setImage();
}

void StoneHP::setData()
{
	TYPE = HP_STONE;
	HP = 10;
	DAMAGE = 0;
	MP = 0;
}

void StoneHP::setImage()
{
	//background = Qt::red;
	background = QPixmap(":/stone/Resources/stone/background.png");
	foreground = QPixmap(":/stone/Resources/stone/hp.png");
}
