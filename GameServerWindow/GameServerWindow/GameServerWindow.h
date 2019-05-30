#pragma once

#include <QtWidgets/QMainWindow>
#include <QTcpServer>
#include "Server.h"
#include "ui_GameServerWindow.h"

class GameServerWindow : public QMainWindow
{
	Q_OBJECT

public:
	GameServerWindow(QWidget *parent = Q_NULLPTR);

public slots:
	void changeLabel(QString);

private:
	void setupServer();

private:
	Ui::GameServerWindowClass ui;
	Server* server;
	QList<QTcpSocket*> online;
	QMap<QString, QTcpSocket*> socketMap;
	QList<QPair<QTcpSocket*, QString>> waiting;
	QList<QPair<QTcpSocket*, QTcpSocket*>> playing;
};
