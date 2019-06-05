#pragma once

#include <QtMultimedia/QMediaPlayer>
#include <QMediaPlaylist>


class Sound
{
public:
	Sound();
	~Sound();
	static void initial();
	static void initialVolume();
	static QMediaPlaylist *BGMPlaylist;
	static QMediaPlayer *BGMPlayer;
	static QMediaPlayer *SEPlayer;
	static void writeFile();

};



