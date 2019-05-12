#pragma once
#include <QObject>
#include "Stone.h"
class StoneManager : public QObject
{
	Q_OBJECT
public:
	StoneManager(QObject *parent = Q_NULLPTR);
	StoneManager(QObject *parent, uint seed);
	Stone* getStone(int type, QWidget* parent);
	Stone* getStone(QWidget* parent);
	void changeStone(Stone*& source, int dest, QWidget* parent);
};

