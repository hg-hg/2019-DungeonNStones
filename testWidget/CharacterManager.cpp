#include "stdafx.h"
#include "CharacterManager.h"

CharacterManager* CharacterManager::instance = nullptr;

CharacterManager* CharacterManager:: getInstance() {
	if (instance == nullptr) {
		instance = new CharacterManager();
		atexit(release);
	}
	return instance;
}

CharacterManager::CharacterManager(QObject *parent)
	: QObject(parent)
{
	initialize();
}

CharacterManager::~CharacterManager()
{
}

void CharacterManager::release()
{
	if (instance) {
		delete instance;
		instance = nullptr;
	}
}

Character* CharacterManager::getCharacter(QString name) const
{
	return characters[name];
}

void CharacterManager::readCharacter(QFile& file)
{
	if (!file.open(QFile::ReadOnly | QFile::Text)) {
		qDebug(); return;
	}
	QTextStream in(&file);
	QString name, description, skin, skill;
	int cost, hp, mp;
	name = in.readLine();
	description = in.readLine();
	in >> cost >> hp >> mp;
	in >> skin;
	auto character = new Character(this, name, description, cost, hp, mp, skin);
	while (!in.atEnd()) {
		in >> skill;
		character->skills.append(skill);
	}
	characters.insert(name, character);
}

void CharacterManager::initialize()
{
	QDir dir("./character");
	if (!dir.exists()) {
		qDebug();
		return;
	}

	QStringList filter;
	filter << QString("*.txt");
	dir.setFilter(QDir::Files | QDir::NoSymLinks);
	dir.setNameFilters(filter);

	for (int i = 0; i < dir.count(); i++) {
		QString name = "./character/" + dir[i];
		QFile file(name);
		readCharacter(file);
	}
		
}
