#pragma once

#include <QObject>
#include <QtGui>
#include "Stone.h"

class CrushAnimation : public QObject
{
Q_OBJECT

	/*functions*/
public:
	explicit CrushAnimation(QObject* parent = Q_NULLPTR);
	void add(Stone* stone);
	/*you can change this function if you like,
		this means to change the location of the stone according to time,
		make sure the stone won't go too far from the previous location*/
	QPoint tremble(int t);
protected:
	/*overide from QObject
		invoke every time*/
	void timerEvent(QTimerEvent* event) override;

private:
	void setup();
	void changeAlpha(Stone* stone);

public slots:
	void animate(int duration);
signals:
	void finished(); //connect to GameBoard::gravity()

	/*members*/
protected:
	/*from QObject*/
	int timerId;
private:
	QList<Stone*> stonesToCrush;
	int t;
	int duration;
	bool isAnimating;
};
