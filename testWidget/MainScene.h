#pragma once

#include <QWidget>
#include "ui_MainScene.h"

class MainScene : public QWidget
{
	Q_OBJECT

public:
	MainScene(QWidget *parent = Q_NULLPTR);
	~MainScene();
	void initButton();

public slots:
	void pvp();
	void pve();
	void shop();
	void quit();
	void setting();

signals:
	void goPVP();
	void goPVE();
	void goShop();
	void goSetting();
	void goQuit();

private:
	Ui::MainScene ui;
};
