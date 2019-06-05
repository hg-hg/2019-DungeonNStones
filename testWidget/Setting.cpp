#include "stdafx.h"
#include "Setting.h"
#include "Sound.h"

int Setting::BGMvolume = 50;
int Setting::SEvolume = 50;
Setting::Setting(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this, BGMvolume, SEvolume);

	ui.backToMain->setPicture(".//Picture//back.bmp");

}

Setting::~Setting()
{
}


void Setting::backToMainScene()
{
	ui.backToMain->zoomPush();
	ui.backToMain->zoomPop();
	QTimer::singleShot(500, this, [=]() {
		emit mainScene();
	});
}

void Setting::changeBGMvolume(int volume)
{
	Sound::BGMplayer->setVolume(volume);
	BGMvolume = volume;
}

void Setting::changeSEvolume(int volume)
{
	Sound::SEplayer->setVolume(volume);
	SEvolume = volume;
}
