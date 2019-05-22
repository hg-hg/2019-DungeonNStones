#include "stdafx.h"
#include "Skill.h"

Skill::Skill(QWidget *parent, QString skillName, QString desc, int skillCost)
	: QPushButton(parent), name(skillName), description(desc), cost(skillCost)
{
	setText(name);
	setToolTip(description + "\ncost: " + QString::number(cost));
	setMouseTracking(true);
	connect(this, SIGNAL(clicked()), this, SLOT(skillClicked()));
}

void Skill::skillClicked()
{
	emit useSkill(name, cost);
}


