#include "stdafx.h"
#include "PVE.h"
#include "Account.h"
#include "CharacterManager.h"

PVE::PVE(QWidget *parent)
	: QWidget(parent)
{
	ui.setupUi(this);
	ui.gameBoard->setData(account, account->getSelectedCharacter(), CharacterManager::getInstance()->getCharacter("AutoRobot"));
	
	
}

PVE::~PVE()
{
}
