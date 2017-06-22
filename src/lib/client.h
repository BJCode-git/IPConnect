/*
 *   This file is part of IPConnect
 *   Copyright 2017 Shashwat Dixit <shashwatdixit124@gmail.com>
 * 
 *   This program is free software; you can redistribute it and/or modify
 *   it under the terms of the GNU Library General Public License as
 *   published by the Free Software Foundation; either version 3 of the
 *   License, or (at your option) any later version.
 * 
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *   GNU General Public License for more details.
 * 
 *   You should have received a copy of the GNU Library General Public
 *   License along with this program; if not, write to the
 *   Free Software Foundation, Inc.,
 *   51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef CLIENT_H
#define CLIENT_H

#include "interfaces/iclient.h"
#include "clientinformation.h"
#include "message.h"

#include <QObject>
#include <QMap>

namespace IPConnect
{

class IConnection;
class SecureTunnel;

class Client : public IClient
{
	Q_OBJECT

public:
	explicit Client(QObject* parent = nullptr);
	~Client();

	IConnection* connection() override;
	ClientInformation info() override;
	void sendMessage(QString ) override;

	void setConnection(IConnection*);
	void setInfo(ClientInformation);
	void start();
	bool hasAcceptedData() const;

public Q_SLOTS:
	void handleRead();
	void closeConnection();

Q_SIGNALS:
	void infoRecieved(ClientInformation);
	void messageRecieved(qint16,QString);
	void connectionClosed();

protected:
	void processRead(QByteArray);
	void handleRequest();
	void send(Message);
	void sendDetail();
	void secured();

	IConnection* m_conn;
	SecureTunnel* m_tunnel;
	ClientInformation m_info;
	Message m_request;
	bool m_detailAccepted;
	bool m_detailSent;
};

}

#endif
