#include "stdafx.h"
#include "Sound.h"
#include <QtConcurrent/QtConcurrent>


Sound* Sound::instance = nullptr;

Sound::Sound(QObject* parent)
	:QObject(parent)
{

}

Sound::~Sound()
{
	emit end();
}

Sound* Sound::getInstance()
{
	if (instance == nullptr)
	{
		instance = new Sound();
		atexit(release);

	}
	return instance;
}

void Sound::release()
{
	if (instance)
	{
		delete instance;
		instance = nullptr;
	}
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

	
	bgm.setVolume(static_cast<qreal>(strList[0].toInt()) / 100.0);
	se = static_cast<qreal>(strList[1].toInt()) / 100.0;
}

void Sound::startBGM()
{
	bgm.setSource(QUrl::fromLocalFile(".//Sound//BGM.wav"));
	bgm.setLoopCount(QSoundEffect::Infinite);
	bgm.play();
}

void Sound::writeFile()
{
	QFile file(".//setting.txt");
	file.open(QFile::WriteOnly | QFile::Text);
	QTextStream out(&file);
	out << QString::number(bgm.volume() * 100.0) + " " + QString::number(se * 100.0);
}

void Sound::playSoundEffect(Music music)
{
	type = music;
	QFuture<void> future = QtConcurrent::run([&]() {
		QString path = ".//Sound//";
		switch (type) {
		case CrushSE:
			path += "Crush.wav";
			break;
		case ClickSE:
			path += "ClickStone.wav";
			break;
		case LegalExchangeSE:
			//path = "legalExchange.wav";
			break;
		case IllegalExchangeSE:
			path += "illegalExchange.wav";
			break;
		case GravitySE:
			path += "Gravity.wav";
			break;
		default:
			return;
		}
		if (!path.endsWith(".wav")) return;
		QSoundEffect effect;
		QEventLoop loop;
		loop.setParent(this);
		effect.setSource(QUrl::fromLocalFile(path));
		effect.setVolume(se);
		effect.play();
		QObject::connect(&effect, &QSoundEffect::playingChanged, [&loop]()
		{
			qDebug() << "finished"; 
			loop.exit();
		});
		QObject::connect(this, &Sound::end, &loop, [&]()
		{
			loop.exit();
		});
		loop.exec();
	});
}

void Sound::endLoops()
{
	emit end();
}

