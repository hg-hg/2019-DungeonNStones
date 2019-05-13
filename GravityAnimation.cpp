#include "stdafx.h"
#include "GravityAnimation.h"

GravityAnimation::GravityAnimation(QObject *parent)
	: QObject(parent)
{
	setup();
}

void GravityAnimation::add(Stone * stone, QPoint endPos)
{
	if (isAnimating) return;
	data.push_back(qMakePair(stone, endPos));
	stone->isAnimating = true;
}

void GravityAnimation::timerEvent(QTimerEvent * event)
{
	vX += accelerationX;
	vY += accelerationY;
	for (auto it = data.begin(); it != data.end(); ) {
		auto pair = *it;
		auto stone = pair.first;
		auto des = pair.second;
		auto p = stone->pos();

		int flag = 2;
		//if flag reach 0, the stone has moved to the postion
		//in case some skill can reverse the gravity, do not delete right, left, and up please

		//move horizental
		if ((vX > 0 && (p.x() + (int)vX) < des.x()) || //move right
			(vX < 0 && (p.x() + (int)vX) > des.x())) //move left
			p.setX(p.x() + (int)vX);
		else {
			p.setX(des.x());
			flag--;
		}

		//move vertical
		if ((vY > 0 && (p.y() + (int)vY < des.y())) || //move down
			(vY < 0 && (p.y() + (int)vY > des.y()))) // move up
			p.setY(p.y() + (int)vY);
		else {
			p.setY(des.y());
			flag--;
		}

		stone->move(p);
		if (!flag) {
			it->first->isAnimating = false;
			it = data.erase(it); 
		}
		else it++;
	}
	if (data.isEmpty()) {
		setup();
		emit finished();
	}
}

void GravityAnimation::animate() {
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

