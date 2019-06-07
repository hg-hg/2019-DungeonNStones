#pragma once

#include <QWidget>
#include <QSize>
#include "const.h"

class Stone : public QWidget
{
	Q_OBJECT
/*functions*/
public:
	Stone(QWidget *parent = Q_NULLPTR);
	Stone(const Stone& stone);
	bool isValid() const;
	QSize sizeHint() const override;
	
	bool match(const Stone* stone) const;

protected:
	void paintEvent(QPaintEvent * event) override;
	void mouseReleaseEvent(QMouseEvent * event) override;
	void enterEvent(QEvent *  event) override;
	void leaveEvent(QEvent * event) override;
signals:
	void clicked(Stone* me);

private:
	virtual void setData();
	virtual void setImage();

/*members*/
public:
	static const int size = 64;
	int TYPE = NORMAL_STONE;
	int HP = 0, DAMAGE = 0, MP = 0;
	QPixmap background;
	QPixmap foreground;
	QPen edge;
	bool isAnimating = false;
private:
	bool mouseHasEntered = false;
	QSize defaultSize = QSize(25, 25);
};
