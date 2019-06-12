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

	auto cha1 = new QMovie(this);
	auto cha2 = new QMovie(this);
	auto cha3 = new QMovie(this);
	auto cha4 = new QMovie(this);
	cha1->setScaledSize(ui.chaPic1->size());
	cha2->setScaledSize(ui.chaPic2->size());
	cha3->setScaledSize(ui.chaPic3->size());
	cha4->setScaledSize(ui.chaPic4->size());
	cha1->setFileName(":/skin/Resources/skin/big_demon_ro.gif");
	cha2->setFileName(":/skin/Resources/skin/knight.gif");
	cha3->setFileName(":/skin/Resources/skin/elf.gif");
	cha4->setFileName(":/skin/Resources/skin/wizzard.gif");
	ui.chaPic1->setMovie(cha1);
	ui.chaPic2->setMovie(cha2);
	ui.chaPic3->setMovie(cha3);
	ui.chaPic4->setMovie(cha4);
	cha1->start();
	cha2->start();
	cha3->start();
	cha4->start();
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
