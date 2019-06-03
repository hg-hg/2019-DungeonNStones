#pragma once

#include <QObject>
#include "Skill.h"

class SkillManager : public QObject
{
Q_OBJECT

public:
	SkillManager(QObject* parent);
	~SkillManager();
	Skill* getSkill(QString skillName, QWidget* parent);
};
