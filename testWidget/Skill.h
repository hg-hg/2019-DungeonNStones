#pragma once

#include <QPushButton>

class Skill : public QPushButton
{
	Q_OBJECT

public:
	explicit Skill(QWidget *parent, QString skillName, QString desc, int skillCost);

signals:
	void useSkill(QString, int);
private slots:
	void skillClicked();
public:
	QString name;
	QString description;
	int cost;
};
