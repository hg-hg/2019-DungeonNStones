#pragma once

#include <QWidget>
#include <QLabel>
#include "Character.h"
#include "ui_MessageWidget.h"
#include "ReturnButton.h"

class MessageWidget : public QWidget
{
	Q_OBJECT

public:
	MessageWidget(QWidget *parent ,Character* character);
	~MessageWidget();
	ReturnButton * getReturnButton();
private:
	void setCharacter(Character *character);
	void initialDisplay();
	void initialReturnEvent();
	void initialLabels();
	void initialDescription();
signals:
	void deleteSignal();
private slots:
	void deleteThis();
private:
	Ui::MessageWidget ui;
	Character * character;
	QVector<QPair<QLabel*, QLabel*>> labels;
	
};
