#pragma once

#include <QWidget>
#include <QMouseEvent>
#include "ui_CharacterWidget.h"
#include "Character.h"
class CharacterWidget : public QWidget
{
	Q_OBJECT

public:
	CharacterWidget(QWidget *parent);
	~CharacterWidget();
	void setCharacter(Character * character);
	Character * getCharacter();
protected:
	void mouseReleaseEvent(QMouseEvent *event) override;
private:
	void initialCharacter();
	void initialClickEvent();
private slots:
	void queryClicked();
signals:
	void querySignal();
	void showMessage(CharacterWidget *);

private:
	Ui::CharacterWidget ui;
	Character * character;
};
