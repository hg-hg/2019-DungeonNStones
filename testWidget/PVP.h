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
	void startGame(const QString& account, const QString& character);
	void enemyDisconnected();
	void continueMatching();
	void escape();
	void stopMatching();
	void quitGame();

signals:
	void mainScene();
private:
	Ui::PVP ui;
};
