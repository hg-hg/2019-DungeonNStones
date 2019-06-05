#pragma once

#include <QPushButton>

class MainSceneButton : public QPushButton
{
	Q_OBJECT

public:
	MainSceneButton(QWidget *parent = Q_NULLPTR);
	~MainSceneButton();

	void zoomPush();
	void zoomPop();
	void setPicture(QString normalImg);
public:
	QString normalImg;
	QString pressImg;
	int pressTimes;
};
