#include "stdafx.h"
#include "SelectButton.h"

SelectButton::SelectButton(QWidget* parent)
	: QPushButton(parent)
{
	initialStyle();
	connect(this, SIGNAL(clicked()), this, SLOT(selectClicked()));
}

SelectButton::~SelectButton()
{
}

void SelectButton::initialStyle()
{
	const auto font = QFont("Microsoft YaHei", 8, 50, true);
	setFont(font);
	setText("SELECT");
	setStyleSheet("color: black");
}

void SelectButton::selectClicked()
{
	emit selectSignal();
}
