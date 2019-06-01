#pragma once

#include <QPushButton>

class ReturnButton : public QPushButton
{
	Q_OBJECT

public:
	ReturnButton(QWidget *parent);
	~ReturnButton();
private:
	void initialStyle();
signals:
	void returnSignal();
private slots:
	void returnClicked();
};
