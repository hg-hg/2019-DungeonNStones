#pragma once

#include <QWidget>

#include "ui_Login.h"
#include <QPainter>
class Login : public QWidget
{
	Q_OBJECT

public:
	Login(QWidget *parent = Q_NULLPTR);
	~Login();
	void paintEvent(QPaintEvent*);
	void keyPressEvent(QKeyEvent * event) override;

public slots:
	void loginToServer();
	void accountInitialized();

signals:
	void mainScene();
private:
	Ui::Login ui;
};
