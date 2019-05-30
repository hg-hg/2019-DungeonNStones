#include "stdafx.h"
#include <QtNetwork>
#include "GameServerWindow.h"
#include "AccountManager.h"
#include "const.h"

GameServerWindow::GameServerWindow(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	setupServer();
}

void GameServerWindow::changeLabel(QString str) {
	ui.label->setText(str);
}

void GameServerWindow::setupServer()
{
	server = new Server(this);
	connect(server, SIGNAL(changeUI(QString)), this, SLOT(changeLabel(QString)));
	if (!server->listen(QHostAddress::Any, 27015)) {
		ui.client->setText("wrong");
	}
	else {
		ui.client->setText("yes");
	}
	//connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

	QString ipAddress;

	if (ipAddress.isEmpty())
		ipAddress = QHostAddress(QHostAddress::LocalHost).toString();
	
	ui.label->setText(tr("The server is running on\n\nIP: %1\nport: %2\n\n"
		"Run the Fortune Client example now.")
		.arg(ipAddress).arg(server->serverPort()));
}

