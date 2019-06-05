#pragma once

#include <QWidget>
#include "ui_Setting.h"

class Setting : public QWidget
{
	Q_OBJECT

public:
	Setting(QWidget *parent = Q_NULLPTR);
	~Setting();

private:
	void initialSlider();

private slots:
	void backToMainScene();
	void changeBGMVolume(int);
	void changeSEVolume(int);

signals:
	void mainScene();

private:
	Ui::Setting ui;


};
