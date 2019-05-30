#include "stdafx.h"
#include "GameServerWindow.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	GameServerWindow w;
	w.show();
	return a.exec();
}
