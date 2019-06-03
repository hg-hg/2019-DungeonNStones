#include "stdafx.h"
#include "ReturnButton.h"

ReturnButton::ReturnButton(QWidget* parent)
	: QPushButton(parent)
{
	initialStyle();
	setPicture(".//Picture//back.bmp");
	connect(this, SIGNAL(clicked()), this, SLOT(returnClicked()));
}

ReturnButton::~ReturnButton() = default;

void ReturnButton::initialStyle()
{
	/*auto font = QFont("Microsoft YaHei", 8, 50, true);
	setFont(font);
	setText("RETURN");
	setStyleSheet("color: black");
	setMaximumSize(70, 40);*/
}

void ReturnButton::zoomPush()
{
	auto animation = new QPropertyAnimation(this, "geometry");
	animation->setDuration(200);
	animation->setStartValue(QRect(this->x(), this->y(), this->width(), this->height()));
	animation->setEndValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
	animation->setEasingCurve(QEasingCurve::OutBounce);
	animation->start();
}

void ReturnButton::zoomPop()
{
	auto animation = new QPropertyAnimation(this, "geometry");
	animation->setDuration(200);
	animation->setStartValue(QRect(this->x(), this->y() + 10, this->width(), this->height()));
	animation->setEndValue(QRect(this->x(), this->y(), this->width(), this->height()));
	animation->setEasingCurve(QEasingCurve::OutBounce);
	animation->start();
}

void ReturnButton::setPicture(const QString& normalImg)
{
	QPixmap pix;
	pix.load(normalImg);
	pix = pix.scaled(pix.width() * 0.7, pix.height() * 0.7);
	this->setFixedSize(pix.width(), pix.height());
	this->setStyleSheet("QPushButton(border:0px)");
	this->setIcon(pix);
	this->setIconSize(QSize(pix.width(), pix.height()));
}

void ReturnButton::returnClicked()
{
	emit returnSignal();
}
