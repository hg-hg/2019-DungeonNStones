#pragma once

#include <QPushButton>

class SelectButton : public QPushButton
{
	Q_OBJECT

public:
	SelectButton(QWidget *parent);
	~SelectButton();
private:
	void initialStyle();
signals:
	void selectSignal();
private slots:
	void selectClicked();
};
