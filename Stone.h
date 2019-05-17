#pragma once

#include <QWidget>
#include <QSize>
#include "const.h"

//QT_BEGIN_NAMESPACE
//class QMouseEvent;
//class QPaintEvent;
//QT_END_NAMESPACE

class Stone : public QWidget
{
	Q_OBJECT
/*functions*/
public:
	Stone(QWidget *parent = Q_NULLPTR);
	Stone(const Stone& stone);
	bool isValid() const;
	QSize sizeHint() const override;
	static const int size = 64;
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
	int TYPE = NORMAL_STONE;
	int HP = 0, DAMAGE = 0, MP = 0;
	QColor background;
	QPixmap foreground;
	QPen edge;
	bool isAnimating = false;
private:
	bool start = false;
	QSize defaultSize = QSize(25, 25);
};
