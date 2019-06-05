#include "stdafx.h"
#include "StoneHD.h"

StoneHD::StoneHD(QWidget *parent)
	: Stone(parent)
{
	setData();
	setImage();
}


void StoneHD::setData()
{
	TYPE = HD_STONE;
	HP = 5;
	DAMAGE = 5;
	MP = 0;
}

void StoneHD::setImage()
{
	//background = Qt::yellow;
	background = QPixmap(":/stone/Resources/stone/background.png");
	foreground = QPixmap(":/stone/Resources/stone/hd.png");
}
