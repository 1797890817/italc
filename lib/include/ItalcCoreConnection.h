/*
 * ItalcCoreConnection.h - declaration of class ItalcCoreConnection
 *
 * Copyright (c) 2008-2010 Tobias Doerffel <tobydox/at/users/dot/sf/dot/net>
 *
 * This file is part of iTALC - http://italc.sourceforge.net
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program (see COPYING); if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 */

#ifndef _ITALC_CORE_CONNECTION_H
#define _ITALC_CORE_CONNECTION_H

#include "ItalcCore.h"
#include "ItalcVncConnection.h"


class ItalcCoreConnection : public QObject
{
	Q_OBJECT
public:
	ItalcCoreConnection( ItalcVncConnection *vncConnection );
	~ItalcCoreConnection();

	ItalcVncConnection *vncConnection()
	{
		return m_vncConn;
	}

	ItalcVncConnection::State state() const
	{
		return m_vncConn->state();
	}

	inline bool isConnected() const
	{
		return m_vncConn->isConnected();
	}

	inline const QString & user() const
	{
		return m_user;
	}

	inline const QString & userHomeDir() const
	{
		return m_userHomeDir;
	}

	void sendGetUserInformationRequest();
	void execCmds( const QString &cmd );
	void startDemo( int port, bool fullscreen = false );
	void stopDemo();
	void lockDisplay();
	void unlockDisplay();
	void logonUser( const QString &uname, const QString &pw,
						const QString &domain );
	void logoutUser();
	void displayTextMessage( const QString &msg );

	void powerOnComputer( const QString &mac );
	void powerDownComputer();
	void restartComputer();
	void disableLocalInputs( bool disabled );

	void setRole( const ItalcCore::UserRole role );


private slots:
	void initNewClient( rfbClient *client );


private:
	static rfbBool handleItalcMessage( rfbClient *cl,
						rfbServerToClientMsg *msg );

	bool handleServerMessage( rfbClient *cl, uint8_t msg );
	void enqueueMessage( const ItalcCore::Msg &msg );


	ItalcVncConnection *m_vncConn;
	SocketDevice m_socketDev;

	QString m_user;
	QString m_userHomeDir;

} ;


#endif