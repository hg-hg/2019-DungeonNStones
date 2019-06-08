#pragma once

#include <QDialog>
#include <QMouseEvent>
#include "ui_ConfirmBox.h"

class ConfirmBox : public QDialog
{
	Q_OBJECT

public:
	ConfirmBox(QWidget *parent = Q_NULLPTR);
	~ConfirmBox();
	void setText(QString text);
protected:
	void mousePressEvent(QMouseEvent *e);
	void mouseMoveEvent(QMouseEvent *e);
	void mouseReleaseEvent(QMouseEvent *e);
private:
	Ui::ConfirmBox ui;
	QPoint last;
};
