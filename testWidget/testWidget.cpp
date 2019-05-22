#include "stdafx.h"
#include "testWidget.h"

testWidget::testWidget(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);
	am->setCurrentAccount("yuri");
	ui.gameBoard->setData(am->getCurrentAccount(),cm->getCharacter("Test"), cm->getCharacter("Test2"));
}

