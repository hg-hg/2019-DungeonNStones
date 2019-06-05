#pragma once

#include <QWidget>
#include "ui_Setting.h"
#include "CommodityWidget.h"
#include "MessageWidget.h"

class Setting : public QWidget
{
	Q_OBJECT

public:
	Setting(QWidget *parent = Q_NULLPTR);
	~Setting();

private:
	static int  BGMvolume;
	static int  SEvolume;

private slots:
	void backToMainScene();
	void changeBGMvolume(int);
	void changeSEvolume(int);

signals:
	void mainScene();

private:
	Ui::Setting ui;


};
