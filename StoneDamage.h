#pragma once

#include "Stone.h"

class StoneDamage : public Stone
{
	Q_OBJECT

public:
	StoneDamage(QWidget *parent = Q_NULLPTR);
	
private:
	void setData() override;
	void setImage() override;
};
