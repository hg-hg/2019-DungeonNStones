#pragma once

#include <QThread>

class BGMThread : public QThread
{
	Q_OBJECT

public:
	BGMThread(QObject *parent);
	~BGMThread();
};
