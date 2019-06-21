#pragma once


#include <QtMultimedia/QSoundEffect>
#include "const.h"
#include <QtMultimedia/QMediaPlayer>

class Sound : public QObject
{
	Q_OBJECT
private:
	Sound(QObject * parent = Q_NULLPTR);
	Sound(const Sound&);
	Sound& operator=(const Sound&);
	~Sound();
private:
	static Sound* instance;
public:
	QSoundEffect bgm;

	qreal se;
	Music type;
	//QString path;
	static Sound* getInstance();
	static void release();

	void initialVolume();
	void startBGM();
	void writeFile();
	void playSoundEffect(Music music);
	void endLoops();
signals:
	void end();
};



