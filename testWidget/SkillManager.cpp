#include "stdafx.h"
#include "SkillManager.h"

SkillManager::SkillManager(QObject *parent)
	: QObject(parent)
{
}

SkillManager::~SkillManager()
{
}

Skill * SkillManager::getSkill(QString skillName, QWidget * parent)
{
	QFile file("./skill/" + skillName + ".txt");
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		qDebug(); return nullptr;
	}
	QTextStream in(&file);
	QString name, description;
	int cost;
	name = in.readLine();
	description = in.readLine();
	in >> cost;
	auto skill = new Skill(parent, name, description, cost);
	return skill;
}
