#include "stdafx.h"
#include "Login.h"
#include "Client.h"
#include <QKeyEvent>


Login::Login(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	auto movie = new QMovie(this);
	movie->setFileName(":/skin/Resources/skin/knight.gif");
	movie->setScaledSize(QSize(ui.characterMovie->size().width(), ui.characterMovie->size().width() * 560 / 320));
	ui.characterMovie->setMovie(movie);
	movie->start();
	ui.stackedWidget->setCurrentWidget(ui.enterAccount);
	connect(Client::getInstance(), SIGNAL(accountInitialized()), this, SLOT(accountInitialized()));
}

Login::~Login()
{
}

void Login::paintEvent(QPaintEvent*)
{
	QPainter painter(this);
	//QPixmap pix;
	//pix.load(".//Background//wall.png");
	//painter.drawPixmap(0, 0, this->width(), this->height(), pix);
}

void Login::keyPressEvent(QKeyEvent* event)
{
	if (event->key() == Qt::Key_Return)
	{
		loginToServer();
	}
}

void Login::accountInitialized()
{
	emit mainScene();
}

void Login::loginToServer()
{
	const auto accountName = ui.account->text();
	if (accountName.isEmpty()) return;
	Client::getInstance()->requestAccount(ui.account->text());
	ui.stackedWidget->setCurrentWidget(ui.waiting);
}
