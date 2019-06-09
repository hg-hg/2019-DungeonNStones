#pragma once

#include <QWidget>
#include "GameBoard.h"
#include "ui_PVP.h"

class PVP : public QWidget
{
Q_OBJECT

public:
	PVP(QWidget* parent = Q_NULLPTR);
	~PVP();
	QString enemyAccount;

public slots:
	void startGame(const QString& account, const QString& character);
	void enemyDisconnected();
	void continueMatching();
	void escape();
	void stopMatching();
	void quitGame();
	void die(QString dead);

signals:
	void mainScene();
private:
	Ui::PVP ui;
	bool started = false;
};
