#pragma once

#include <QWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include "Character.h"

class CharacterWidget : public QWidget
{
	Q_OBJECT

public:
	CharacterWidget(QWidget *parent, Character * character);
	~CharacterWidget();
	QSize sizeHint() const override;
	void setCharacter(Character* character);
	Character* getCharacter() const;
	
protected:
	void paintEvent(QPaintEvent* event) override;
	void mouseReleaseEvent(QMouseEvent * event) override;
	void enterEvent(QEvent * event) override;
	void leaveEvent(QEvent * event) override;
private:
	virtual void setImage();
	void initilalClickEvent();
private slots:
	void quryClicked();
signals:
	void quirySiganl();
signals:	
	void showMessage(CharacterWidget *);
public:
	Character* character;
	QColor background;
	QPixmap foreground;
	QPen edge;
private:
	QSize originSzie = QSize(100, 130);
	bool mouseHasEntered = false;

};
