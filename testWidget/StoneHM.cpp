#include "stdafx.h"
#include "StoneHM.h"

StoneHM::StoneHM(QWidget *parent)
	: Stone(parent)
{
	setData();
	setImage();
}

void StoneHM::setData()
{
	TYPE = HM_STONE;
	HP = 5;
	DAMAGE = 0;
	MP = 5;
}

void StoneHM::setImage()
{
	//background = Qt::darkCyan;
	background = QPixmap(":/stone/Resources/stone/background.png");
	foreground = QPixmap(":/stone/Resources/stone/hm.png");
}
