#pragma once

#include "Stone.h"

class StoneHD : public Stone
{
	Q_OBJECT

public:
	StoneHD(QWidget *parent = Q_NULLPTR);
private:
	void setData() override;
	void setImage() override;
};
