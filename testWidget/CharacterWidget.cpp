#include "stdafx.h"
#include "CharacterWidget.h"

CharacterWidget::CharacterWidget(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

CharacterWidget::~CharacterWidget()
{
	delete character;
}

void CharacterWidget::setCharacter(Character * character)
{
	this->character->setData(character);
	initialCharacter();
	initialClickEvent();
}

Character * CharacterWidget::getCharacter()
{
	return character;
}

void CharacterWidget::queryClicked()
{
	emit showMessage(character->name);
}

void CharacterWidget::mouseReleaseEvent(QMouseEvent * event)
{
	emit querySignal();
}

void CharacterWidget::initialCharacter()
{
	const auto skinPath = ":/skin/Resources/skin/" + character->skin;
	if (character->skin.endsWith(".gif")) 
	{
		auto skin = new QMovie(this);
		skin->setFileName(skinPath);
		auto skinSize = QSize(65, 100);
		auto he = skinSize.height();
		auto wi = skinSize.width();
		if (wi > ui.foreground->size().width())
		{
			he *= ui.foreground->size().width();
			he /= wi;
			wi = ui.foreground->size().width();
		}
		if (he > ui.foreground->size().height())
		{
			wi *= ui.foreground->size().height();
			wi /= he;
			he = ui.foreground->size().height();
		}
		skinSize.setHeight(he);
		skinSize.setWidth(wi);
		skin->setScaledSize(skinSize);
		ui.foreground->setMovie(skin);
		skin->start();
	}
	else
	{
		QPixmap skin(skinPath);
		skin = skin.scaled(ui.foreground->size(), Qt::KeepAspectRatio);
		ui.foreground->setPixmap(skin);
	}
}

void CharacterWidget::initialClickEvent()
{
	connect(this, SIGNAL(querySignal()), this, SLOT(queryClicked()));
}
