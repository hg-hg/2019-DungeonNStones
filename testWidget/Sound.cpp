#include "stdafx.h"
#include "Sound.h"


QMediaPlaylist* Sound::BGMPlaylist = new QMediaPlaylist;
QMediaPlayer* Sound::BGMPlayer = new QMediaPlayer;
QMediaPlayer* Sound::SEPlayer = new QMediaPlayer;

Sound::Sound()
{
	initialVolume();
	BGMPlaylist->addMedia(QUrl("./Sound/BGM.wav"));
	BGMPlaylist->setCurrentIndex(1);
	BGMPlaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
	BGMPlayer->setPlaylist(BGMPlaylist);
	//BGMPlayer->setVolume(50);
	BGMPlayer->play();
	//SEPlayer->setVolume(50);
}


Sound::~Sound()
{
}

void Sound::initialVolume()
{
	QFile file(".//Sound//setting.txt");
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		writeFile();
		return;
	}
	QTextStream in(&file);
	const auto str = in.readAll().simplified();
	const auto strList = str.split(" ");
	if (strList.size() != 2)
	{
		writeFile();
		return;
	}
	BGMPlayer->setVolume(strList[0].toInt());
	SEPlayer->setVolume(strList[1].toInt());
}

void Sound::writeFile()
{
	QFile file(".//Sound//setting.txt");
	file.open(QFile::WriteOnly | QFile::Text);
	QTextStream out(&file);
	out << QString::number(BGMPlayer->volume()) + " " + QString::number(SEPlayer->volume());
}

