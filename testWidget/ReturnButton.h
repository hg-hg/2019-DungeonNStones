#pragma once

#include <QPushButton>

class ReturnButton : public QPushButton
{
	Q_OBJECT

public:
	ReturnButton(QWidget *parent);
	~ReturnButton();
	void setPicture(QString normalImg);
	void ZoomPush();
	void ZoomPop();
private:
	void initialStyle();
signals:
	void returnSignal();
private slots:
	void returnClicked();
};
