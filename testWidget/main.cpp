#include "stdafx.h"
#include "testWidget.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	QFont font;
	int id = QFontDatabase::addApplicationFont(":/font/Resources/font/monogram_extended.ttf");
	QStringList loadedFontFamilies = QFontDatabase::applicationFontFamilies(id);
	if (!loadedFontFamilies.isEmpty()) font = loadedFontFamilies.at(0);
	font.setPointSize(25);
	testWidget w;
	//w.setFont(font);
	a.setFont(font);
	w.show();
	return a.exec();
}
