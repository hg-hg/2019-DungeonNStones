#pragma once

#include <QWidget>
#include "ui_PVE.h"

class PVE : public QWidget
{
	Q_OBJECT

public:
	PVE(QWidget *parent = Q_NULLPTR);
	~PVE();
	
private:
	void confirm();

signals:
	void mainScene();

public slots:
	void playerDead(QString playerAccount);
	void escape();

private:
	Ui::PVE ui;
};
