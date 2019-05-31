#pragma once

#include <QWidget>
#include "Client.h"
#include "GameBoard.h"
#include "ui_PVP.h"

class PVP : public QWidget
{
	Q_OBJECT

public:
	PVP(QWidget *parent = Q_NULLPTR);
	~PVP();
	QString enemyAccount;

public slots:
	void gameStart(QString account, QString character);
	void enemyDisconnected();
private:
	Ui::PVP ui;
};
