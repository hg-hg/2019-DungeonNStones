#pragma once

#include <QPushButton>

class MainSceneButton : public QPushButton
{
	Q_OBJECT

public:
	MainSceneButton(QWidget *parent = Q_NULLPTR);
	~MainSceneButton();

	void ZoomPush();
	void ZoomPop();
	void setPicture(QString normalImg);
public:
	QString normalImg;
	QString pressImg;
	int pressTimes;
};
