#include "stdafx.h"
#include "SkillManager.h"

SkillManager::SkillManager(QObject* parent)
	: QObject(parent)
{
}

SkillManager::~SkillManager()
{
}

Skill* SkillManager::getSkill(const QString skillName, QWidget* parent)
{
	QFile file("./skill/" + skillName + ".txt");
	if (!file.open(QFile::ReadOnly | QFile::Text))
	{
		qDebug();
		return nullptr;
	}
	QTextStream in(&file);
	int cost;
	const auto name = in.readLine();
	const auto description = in.readLine();
	in >> cost;
	const auto skill = new Skill(parent, name, description, cost);
	return skill;
}
