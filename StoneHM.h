#pragma once

#include "Stone.h"

class StoneHM : public Stone
{
	Q_OBJECT

public:
	StoneHM(QWidget *parent = Q_NULLPTR);
private:
	void setData() override;
	void setImage() override;
};
