#include "stdafx.h"
#include "Stone.h"

Stone::Stone(QWidget *parent)
	: QWidget(parent)
{
	setData();
	setImage();
}

Stone::Stone(const Stone & stone)
{
	TYPE = stone.TYPE;
	HP = stone.HP;
	DAMAGE = stone.DAMAGE;
	MP = stone.MP;
}

bool Stone::isValid() const
{
	if (this == nullptr) return false;
	return TYPE >= 0;
}

QSize Stone::sizeHint() const
{
	return QSize(50, 50);
}

bool Stone::match(const Stone * stone) const
{
	if (this == nullptr || stone == nullptr) return false;
	return this->TYPE == stone->TYPE;
}

void Stone::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	painter.fillRect(event->rect(), QBrush(background));
	painter.drawPixmap(rect(), foreground);
}

void Stone::mouseReleaseEvent(QMouseEvent *) {
	emit clicked(this);
}

void Stone::setData()
{
	HP = 3;
	DAMAGE = 3;
	MP = 3;
}

void Stone::setImage()
{
	background = Qt::white;
	foreground = QPixmap("icon.png");
}

