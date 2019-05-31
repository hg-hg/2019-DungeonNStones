#pragma once

#include <QWidget>
#include "ui_Login.h"

class Login : public QWidget
{
	Q_OBJECT

public:
	Login(QWidget *parent = Q_NULLPTR);
	~Login();

public slots:
	void loginToServer();

private:
	Ui::Login ui;
};
