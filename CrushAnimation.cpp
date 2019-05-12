#include "stdafx.h"
#include "CrushAnimation.h"

CrushAnimation::CrushAnimation(QObject *parent)
	: QObject(parent)
{
	setup();
}

void CrushAnimation::add(Stone * stone)
{
	if (isAnimating) return;
	stonesToCrush.push_back(stone);
}

QPoint CrushAnimation::tremble(int t)
{
	/*QMessageBox::information(NULL, "test", "");*/
	return QPoint((int) 3 * cos(3 * t), (int) 3 * sin(5 * t));
}

void CrushAnimation::timerEvent(QTimerEvent * event)
{
	if (t < duration) {
		t++;
		for (auto& widget : stonesToCrush) widget->move(tremble(t) + widget->pos());
	}
	else {
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

void CrushAnimation::animate(int duration) {
	timerId = startTimer(30);
	this->duration = duration;
	isAnimating = true;
}
