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
	ui.bgm->setValue(Sound::BGMPlayer->volume());
	ui.se->setValue(Sound::SEPlayer->volume());
}


void Setting::backToMainScene()
{
	QTimer::singleShot(500, this, [=]() {
		emit mainScene();
	});
}

void Setting::changeBGMVolume(const int volume)
{
	Sound::BGMPlayer->setVolume(volume);
}

void Setting::changeSEVolume(const int volume)
{
	Sound::SEPlayer->setVolume(volume);
}
