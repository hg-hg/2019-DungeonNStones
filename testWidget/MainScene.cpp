#include "stdafx.h"
#include "MainScene.h"
#include <QTimer>
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
	ui.PVP->ZoomPush();
	ui.PVP->ZoomPop();
	QTimer::singleShot(500, this, [=]() {
		emit goPVP();
	});
}

void MainScene::pve()
{
	ui.PVE->ZoomPush();
	ui.PVE->ZoomPop();
	QTimer::singleShot(500, this, [=]() {
		emit goPVE();
	});
}

void MainScene::shop()
{
	ui.shopBoard->ZoomPush();
	ui.shopBoard->ZoomPop();
	QTimer::singleShot(500, this, [=]() {
		emit goShop();
	});
	
}

void MainScene::quit()
{
	ui.Quit->ZoomPush();
	ui.Quit->ZoomPop();
	QTimer::singleShot(500, this, [=]() {
		emit goQuit();
	});
	
}
void MainScene::paintEvent(QPaintEvent*) {
	QPainter painter(this);
	//QPixmap pix;
	//pix.load(".//Background//wall_complex.png");
	//painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}
void MainScene::setting()
{
	ui.Setting->ZoomPush();
	ui.Setting->ZoomPop();
	QTimer::singleShot(500, this, [=]() {
		emit goSetting();
	});
	
}
