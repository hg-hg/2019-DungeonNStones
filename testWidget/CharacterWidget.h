#pragma once

#include <QWidget>
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
	void initialClickEvent();
private slots:
	void queryClicked();
signals:
	void querySignal();
	void showMessage(CharacterWidget *);
public:
	Character* character;
	QColor background;
	QPixmap foreground;
	QPen edge;
private:
	QSize originSize = QSize(100, 130);
	bool mouseHasEntered = false;

};
