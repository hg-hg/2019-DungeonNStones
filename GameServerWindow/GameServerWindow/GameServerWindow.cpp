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

void GameServerWindow::setupServer()
{
	server = new Server(this);
	if (!server->listen(QHostAddress("192.168.1.243"), 10086)) {
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

