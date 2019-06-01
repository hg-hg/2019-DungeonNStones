#include "stdafx.h"
#include "MainScene.h"

MainScene::MainScene(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	initButton();
}

MainScene::~MainScene()
{
}

void MainScene::initButton()
{
	ui.PVE->setPicture(".//Picture//PVE.bmp");
	ui.PVP->setPicture(".//Picture//PVP.bmp");
	ui.Quit->setPicture(".//Picture//exit.bmp");
	ui.Setting->setPicture(".//Picture//Setting.bmp");
	ui.shopBoard->setPicture(".//Picture//shop.bmp");
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

