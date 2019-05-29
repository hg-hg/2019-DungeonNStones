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
	Ui::PVE ui;
	Account * account = Account::getInstance();
};
