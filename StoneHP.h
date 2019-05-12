#pragma once

#include "Stone.h"

class StoneHP : public Stone
{
	Q_OBJECT

public:
	StoneHP(QWidget *parent = Q_NULLPTR);

private:
	void setData() override;
	void setImage() override;

public:
	
};
