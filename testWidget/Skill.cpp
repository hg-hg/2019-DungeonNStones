#include "stdafx.h"
#include "Skill.h"

Skill::Skill(QWidget *parent, QString skillName, QString desc, int skillCost)
	: QPushButton(parent), name(skillName), description(desc), cost(skillCost)
{
	setText(name);
	if (skillName == "damage" || skillName == "heal") {
		timer = new QTimer(this);
		connect(timer, SIGNAL(timeout()), this, SLOT(skillClicked()));
		timer->start(10000);
	}
	setToolTip(description + "\ncost: " + QString::number(cost));
	setMouseTracking(true);
	connect(this, SIGNAL(clicked()), this, SLOT(skillClicked()));
}

void Skill::skillClicked()
{
	emit useSkill(name, cost);
}
