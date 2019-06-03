#pragma once

#include <QObject>
#include "Stone.h"

class GravityAnimation : public QObject
{
Q_OBJECT

public:
	explicit GravityAnimation(QObject* parent = Q_NULLPTR);
	void add(Stone* stone, QPoint endPos);

protected:
	void timerEvent(QTimerEvent* event) override;

private:
	void setup();
signals:
	void finished();

public slots:
	void animate();

public:
	qreal accelerationX = 0;
	qreal accelerationY = 5;
protected:
	int timerId;

private:
	QStack<QPair<Stone*, QPoint>> data;
	bool isAnimating;
	qreal vX;
	qreal vY;
};
