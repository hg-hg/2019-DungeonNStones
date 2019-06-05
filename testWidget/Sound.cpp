#include "stdafx.h"
#include "Sound.h"


QMediaPlaylist* Sound::BGMplaylist = new QMediaPlaylist;
QMediaPlayer* Sound::BGMplayer = new QMediaPlayer;
QMediaPlayer* Sound::SEplayer = new QMediaPlayer;

Sound::Sound()
{
	BGMplaylist->addMedia(QUrl("./Sound/BGM.wav"));
	BGMplaylist->setCurrentIndex(1);
	BGMplaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
	BGMplayer->setPlaylist(BGMplaylist);
	BGMplayer->setVolume(50);
	BGMplayer->play();
	SEplayer->setVolume(50);
}


Sound::~Sound()
{
}

