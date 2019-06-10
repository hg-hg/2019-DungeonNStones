#include "stdafx.h"
#include "MainScene.h"
#include <QTimer>
MainScene::MainScene(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	auto logo = new QMovie(this);
	logo->setFileName(":/word/Resources/word/Title_pic.gif");
	ui.logoPic->setMovie(logo);
	logo->start();
}

MainScene::~MainScene()
{
}

void MainScene::pvp()
{
	QTimer::singleShot(500, this, [=]() {
		emit goPVP();
	});
}

void MainScene::pve()
{
	QTimer::singleShot(500, this, [=]() {
		emit goPVE();
	});
}

void MainScene::shop()
{
	QTimer::singleShot(500, this, [=]() {
		emit goShop();
	});
	
}

void MainScene::quit()
{
	QTimer::singleShot(500, this, [=]() {
		emit goQuit();
	});
	
}

void MainScene::setting()
{
	QTimer::singleShot(500, this, [=]() {
		emit goSetting();
	});
	
}
