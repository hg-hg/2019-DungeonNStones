#pragma once
#include <QPushButton>

class BuyButton : public QPushButton
{
	Q_OBJECT

public:
	BuyButton(QWidget *parent);
	~BuyButton();
private:
	void initialStyle();
signals:
	void buySignal();
private slots:
	void buyClicked();
};
