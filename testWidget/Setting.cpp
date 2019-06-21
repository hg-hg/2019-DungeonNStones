#include "stdafx.h"
#include "Setting.h"
#include "Sound.h"

Setting::Setting(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initialSlider();
}


Setting::~Setting()
{
}

void Setting::initialSlider()
{
	ui.bgm->setValue(Sound::getInstance()->bgm.volume() * 100.0);
	ui.se->setValue(Sound::getInstance()->se * 100.0);
}


void Setting::backToMainScene()
{
	QTimer::singleShot(500, this, [=]() {
		emit mainScene();
	});
}

void Setting::changeBGMVolume(const int volume)
{
	Sound::getInstance()->bgm.setVolume(static_cast<qreal>(volume) / 100.0);
}

void Setting::changeSEVolume(const int volume)
{
	Sound::getInstance()->se = static_cast<qreal>(volume) / 100.0;
}
