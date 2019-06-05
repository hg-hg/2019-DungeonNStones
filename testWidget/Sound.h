#pragma once

#include <QtMultimedia/QMediaPlayer>
#include <QMediaPlaylist>

class Sound
{
public:
	Sound();
	~Sound();
	static QMediaPlaylist *BGMplaylist;
	static QMediaPlayer *BGMplayer;
	static QMediaPlayer *SEplayer;

};



