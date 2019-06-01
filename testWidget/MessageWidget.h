#pragma once

#include <QWidget>
#include <QSize>
#include <QTextBrowser>
#include <QGridLayout>
#include "Character.h"
#include "BuyButton.h"
#include "ReturnButton.h"

class MessageWidget : public QWidget
{
	Q_OBJECT

public:
	MessageWidget(QWidget *parent,Character * character);
	~MessageWidget();
	QSize sizeHint() const override;
	ReturnButton * getReturnButton();
private:
	void setCharacter(Character * character);
	void initialLayout();
	void initialDisplay();
	void initialReturnButton();
	void initialReturnEvent();
signals:
	void deleteSignal();
private slots:
	void deleteThis();
private:
	Character* character;
	QSize originSize = QSize(600,1000);
	QTextBrowser* displayFlied;
	ReturnButton * returnButton;
};
