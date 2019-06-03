#include "stdafx.h"
#include "ExchangeAnimation.h"

ExchangeAnimation::ExchangeAnimation(QObject* parent)
	: QObject(parent)
{
}

void ExchangeAnimation::legalExchange(Stone* one, Stone* two)
{
	first = one;
	second = two;
	first->isAnimating = true;
	second->isAnimating = true;
	/*do not use QRect(QWidget*->rect())!!! I have wasted time finding this problem!!!
		Or nothing changed at all, please refer to the doc to find out the reason*/
	auto a1 = new QPropertyAnimation(one, "geometry");
	a1->setDuration(normalTime);
	a1->setStartValue(QRect(one->x(), one->y(), one->width(), one->height()));
	a1->setEndValue(QRect(two->x(), two->y(), one->width(), one->height()));

	auto a2 = new QPropertyAnimation(two, "geometry");
	a2->setDuration(normalTime);
	a2->setStartValue(QRect(two->x(), two->y(), one->width(), one->height()));
	a2->setEndValue(QRect(one->x(), one->y(), one->width(), one->height()));

	/*QParallelAnimationGroup can make members animate at same time*/
	auto group = new QParallelAnimationGroup();
	group->addAnimation(a1);
	group->addAnimation(a2);
	group->start(QAbstractAnimation::DeleteWhenStopped);
	connect(group, SIGNAL(finished()), this, SLOT(sendFinishedMessage()));
}

void ExchangeAnimation::illegalExchange(Stone* one, Stone* two)
{
	first = one;
	second = two;
	first->isAnimating = true;
	second->isAnimating = true;

	const auto dx = one->x() - two->x();
	const auto dy = one->y() - two->y();

	auto a1 = new QPropertyAnimation(one, "geometry");
	a1->setDuration(fastTime);
	a1->setStartValue(QRect(one->x(), one->y(), one->width(), one->height()));
	a1->setEndValue(QRect(one->x() - dx / 3, one->y() - dy / 3, one->width(), one->height()));

	auto a2 = new QPropertyAnimation(one, "geometry");
	a2->setDuration(fastTime);
	a2->setStartValue(QRect(one->x() - dx / 3, one->y() - dy / 3, one->width(), one->height()));
	a2->setEndValue(QRect(one->x(), one->y(), one->width(), one->height()));

	/*QSequentialAnimationGroup makes its members to animate one by one, instead of doing together*/
	auto group1 = new QSequentialAnimationGroup();
	group1->addAnimation(a1);
	group1->addAnimation(a2);

	auto a3 = new QPropertyAnimation(two, "geometry");
	a3->setDuration(fastTime);
	a3->setStartValue(QRect(two->x(), two->y(), two->width(), two->height()));
	a3->setEndValue(QRect(two->x() + dx / 3, two->y() + dy / 3, two->width(), two->height()));

	auto a4 = new QPropertyAnimation(two, "geometry");
	a4->setDuration(fastTime);
	a4->setStartValue(QRect(two->x() + dx / 3, two->y() + dy / 3, two->width(), two->height()));
	a4->setEndValue(QRect(two->x(), two->y(), two->width(), two->height()));

	auto group2 = new QSequentialAnimationGroup();
	group2->addAnimation(a3);
	group2->addAnimation(a4);

	auto group = new QParallelAnimationGroup();
	group->addAnimation(group1);
	group->addAnimation(group2);
	group->start(QAbstractAnimation::DeleteWhenStopped);
	connect(group, SIGNAL(finished()), this, SLOT(sendFinishedMessage()));
}

void ExchangeAnimation::sendFinishedMessage()
{
	first->isAnimating = false;
	second->isAnimating = false;
	emit(finished());
}
