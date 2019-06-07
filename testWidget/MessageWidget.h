#pragma once

#include <QWidget>
#include <QLabel>
#include "Character.h"
#include "ui_MessageWidget.h"

class MessageWidget : public QWidget
{
	Q_OBJECT

public:
	MessageWidget(QWidget *parent ,Character* character);
	~MessageWidget();
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
	Character * character = new Character(this);
	QVector<QPair<QLabel*, QLabel*>> labels;
	
};
