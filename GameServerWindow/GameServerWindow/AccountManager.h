#pragma once

#include <QObject>
#include <QTcpSocket>

class AccountManager : public QObject
{
	Q_OBJECT

public:
	AccountManager(QObject *parent = Q_NULLPTR);
	~AccountManager();
	QString getAccount(QString accountName);
	void setAccount(QString accountName, QString str);
	QTcpSocket* socket;
};
