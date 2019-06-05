#include "stdafx.h"
#include "GravityAnimation.h"
#include "Sound.h"

GravityAnimation::GravityAnimation(QObject* parent)
	: QObject(parent)
{
	setup();
}

void GravityAnimation::add(Stone* stone, const QPoint endPos)
{
	if (isAnimating) return;
	data.push_back(qMakePair(stone, endPos));
	stone->isAnimating = true;
}

void GravityAnimation::timerEvent(QTimerEvent* event)
{
	vX += accelerationX;
	vY += accelerationY;
	for (auto it = data.begin(); it != data.end();)
	{
		auto pair = *it;
		auto stone = pair.first;
		auto des = pair.second;
		auto p = stone->pos();

		auto flag = 2;
		//if flag reach 0, the stone has moved to the position
		//in case some skill can reverse the gravity, do not delete right, left, and up please

		//move horizontal
		if ((vX > 0 && (p.x() + static_cast<int>(vX)) < des.x()) || //move right
			(vX < 0 && (p.x() + static_cast<int>(vX)) > des.x())) //move left
			p.setX(p.x() + static_cast<int>(vX));
		else
		{
			p.setX(des.x());
			flag--;
		}

		//move vertical
		if ((vY > 0 && (p.y() + static_cast<int>(vY) < des.y())) || //move down
			(vY < 0 && (p.y() + static_cast<int>(vY) > des.y()))) // move up
			p.setY(p.y() + static_cast<int>(vY));
		else
		{
			p.setY(des.y());
			flag--;
		}

		stone->move(p);
		if (!flag)
		{
			stone->isAnimating = false;
			it = data.erase(it);
		}
		else it++;
	}
	if (data.isEmpty())
	{
		setup();
		emit finished();
	}
}

void GravityAnimation::animate()
{
	Sound::SEPlayer->setMedia(QUrl("./Sound/Gravity.wav"));
	Sound::SEPlayer->play();
	timerId = startTimer(40);
	isAnimating = true;
}

void GravityAnimation::setup()
{
	vX = vY = 0;
	data.clear();
	killTimer(timerId);
	isAnimating = false;
}
