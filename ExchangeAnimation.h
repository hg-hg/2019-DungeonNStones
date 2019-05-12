#pragma once

#include <QObject>
#include "Stone.h"
class ExchangeAnimation : public QObject
{
	Q_OBJECT

public:
	ExchangeAnimation(QObject *parent = Q_NULLPTR);
	void legalExchange(Stone* one, Stone* two);
	void illegalExchange(Stone* one, Stone* two);

signals:
	void finished();

private slots:
	void sendFinishedMessage();
};
