#include "stdafx.h"
#include "Client.h"

Client::Client(QObject *parent)
	: QTcpSocket(parent)
{
}

Client::~Client()
{
}
