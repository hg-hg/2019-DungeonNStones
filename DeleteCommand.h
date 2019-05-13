#pragma once

#include <QObject>

class DeleteCommand : public QObject
{
	Q_OBJECT

public:
	DeleteCommand(QObject *parent);
	
};
