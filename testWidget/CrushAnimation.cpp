#include "stdafx.h"
#include "CrushAnimation.h"
#include "Sound.h"

CrushAnimation::CrushAnimation(QObject* parent)
	: QObject(parent)
{
	setup();
}

void CrushAnimation::add(Stone* stone)
{
	if (isAnimating) return;
	stone->isAnimating = true;
	stonesToCrush.push_back(stone);
}

QPoint CrushAnimation::tremble(const int t)
{
	/*all magic number, change if you want, 
	but make sure the stone location stay around it previous location*/
	return QPoint(static_cast<int>(3) * cos(3 * t), static_cast<int>(3) * sin(3 * t));
}

void CrushAnimation::timerEvent(QTimerEvent* event)
{
	if (t < duration)
	{
		t++;
		for (auto& stone : stonesToCrush)
		{
			stone->move(tremble(t) + stone->pos());
			changeAlpha(stone);
		}
	}
	else
	{
		for (auto& stone : stonesToCrush) stone->isAnimating = false;
		setup();
		emit finished();
	}
}

void CrushAnimation::setup()
{
	killTimer(timerId);
	stonesToCrush.clear();
	t = 0;
	isAnimating = false;
}

void CrushAnimation::changeAlpha(Stone* stone)
{
	auto alpha = 256 / duration * t;
	if (alpha > 256) alpha = 256;
	//stone->background.setAlpha(alpha);
}

void CrushAnimation::animate(const int duration)
{
	Sound::SEPlayer->setMedia(QUrl("./Sound/Crush.wav"));
	Sound::SEPlayer->play();
	timerId = startTimer(30);
	this->duration = duration;
	isAnimating = true;
}
