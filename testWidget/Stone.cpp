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
	return QSize(size, size);
}

bool Stone::match(const Stone * stone) const
{
	if (this == nullptr || stone == nullptr) return false;
	return this->TYPE == stone->TYPE;
}

void Stone::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	//foreground = foreground.scaled(defaultSize, Qt::KeepAspectRatio);
	painter.fillRect(event->rect(), QBrush(background));
	painter.drawPixmap(rect(), foreground);
	if (mouseHasEntered) {
		painter.setPen(edge);
		painter.drawRect(rect());
	}
}

void Stone::mouseReleaseEvent(QMouseEvent *) {
	if (isAnimating) {
		qDebug();
		return; 
	}
	emit clicked(this);
}

void Stone::enterEvent(QEvent * event)
{
	mouseHasEntered = true;
	edge.setColor(QColor(0xFF, 0xFA, 0xCD, 0xDD));
	edge.setWidth(5);
	update();
}

void Stone::leaveEvent(QEvent * event)
{
	edge.setColor(background);
	update();
}

void Stone::setData()
{
	HP = 3;
	DAMAGE = 3;
	MP = 3;
}

void Stone::setImage()
{
	background = Qt::black;
	foreground = QPixmap(":/foreground/Resources/foreground/icon.png");
}
