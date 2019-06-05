#include "stdafx.h"
#include "StoneMP.h"

StoneMP::StoneMP(QWidget *parent)
	: Stone(parent)
{
	setData();
	setImage();
}

void StoneMP::setData()
{
	TYPE = MP_STONE;
	HP = 0;
	DAMAGE = 0;
	MP = 10;
}

void StoneMP::setImage()
{
	//background = Qt::blue;
	background = QPixmap(":/stone/Resources/stone/background.png");
	foreground = QPixmap(":/stone/Resources/stone/mp.png");
}
