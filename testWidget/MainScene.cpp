#include "stdafx.h"
#include "MainScene.h"

MainScene::MainScene(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
}

MainScene::~MainScene()
{
}

void MainScene::pvp()
{
	emit goPVP();
}

void MainScene::pve()
{
	emit goPVE();
}

void MainScene::shop()
{
	emit goShop();
}

void MainScene::quit()
{
	emit goQuit();
}

void MainScene::setting()
{
	emit goSetting();
}
