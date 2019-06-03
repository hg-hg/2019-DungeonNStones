#include "stdafx.h"
#include "Login.h"
#include "Client.h"
#include <QKeyEvent>


Login::Login(QWidget* parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	auto movie = new QMovie(".//skin//knight_m_idle_anim_f0.gif");
	movie->setScaledSize(QSize(ui.label_2->size().width(), ui.label_2->size().width() * 560 / 320));
	ui.label_2->setMovie(movie);
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
