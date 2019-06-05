#include "stdafx.h"
#include "Sound.h"


QMediaPlaylist* Sound::BGMPlaylist = new QMediaPlaylist;
QMediaPlayer* Sound::BGMPlayer = new QMediaPlayer;
QMediaPlayer* Sound::SEPlayer = new QMediaPlayer;

Sound::Sound()
{

}


Sound::~Sound()
{
}

void Sound::initial()
{
	BGMPlayer->setVolume(50);
	SEPlayer->setVolume(50);
	initialVolume();
	BGMPlaylist->addMedia(QUrl("qrc:/sound/Resources/Sound/BGM.wav"));
	BGMPlaylist->setCurrentIndex(1);
	BGMPlaylist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
	BGMPlayer->setPlaylist(BGMPlaylist);
	//BGMPlayer->setVolume(50);
	BGMPlayer->play();
	//SEPlayer->setVolume(50);
}

void Sound::initialVolume()
{
	QFile file(".//setting.txt");
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
	QFile file(".//setting.txt");
	file.open(QFile::WriteOnly | QFile::Text);
	QTextStream out(&file);
	out << QString::number(BGMPlayer->volume()) + " " + QString::number(SEPlayer->volume());
}

