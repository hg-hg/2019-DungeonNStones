#include "stdafx.h"
#include "CharacterWidget.h"

CharacterWidget::CharacterWidget(QWidget *parent, Character * character)
	: QWidget(parent)
{
	setCharacter(character);
	setImage();
	initialClickEvent();
}

CharacterWidget::~CharacterWidget()
{
}

QSize CharacterWidget::sizeHint() const
{
	return originSize;
}

void CharacterWidget::setCharacter(Character *character)
{
	this->character = character;
}

Character * CharacterWidget::getCharacter() const
{
	return character;
}

void CharacterWidget::paintEvent(QPaintEvent* event)
{
	QPainter painter(this);
	painter.fillRect(event->rect(), QBrush(background));
	painter.drawPixmap(foreground.rect(), foreground);
	if (mouseHasEntered) {
		painter.setPen(edge);
		painter.drawRect(rect());
	}
}

void CharacterWidget::mouseReleaseEvent(QMouseEvent * event)
{
	emit querySignal();
}

void CharacterWidget::enterEvent(QEvent * event)
{
	mouseHasEntered = true;
	edge.setColor(QColor(0xFF, 0xFA, 0xCD, 0xDD));
	edge.setWidth(10);
	update();
}

void CharacterWidget::leaveEvent(QEvent * event)
{
	edge.setColor(background);
	update();
}

void CharacterWidget::queryClicked()
{
	emit showMessage(this);
}

void CharacterWidget::setImage()
{
	background = Qt::white;
	foreground = QPixmap("./skin/" + character->skin);
	foreground = foreground.scaled(QSize(100, 130));
}

void CharacterWidget::initialClickEvent()
{
	connect(this, SIGNAL(querySignal()), this, SLOT(queryClicked()));
}

