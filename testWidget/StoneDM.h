#pragma once

#include "Stone.h"

class StoneDM : public Stone
{
	Q_OBJECT

public:
	StoneDM(QWidget *parent = Q_NULLPTR);
private:
	void setData() override;
	void setImage() override;
};
