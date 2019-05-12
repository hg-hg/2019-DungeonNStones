#pragma once

#include "Stone.h"

class StoneMP : public Stone
{
	Q_OBJECT

public:
	StoneMP(QWidget *parent = Q_NULLPTR);

private:
	void setData() override;
	void setImage() override;
};
