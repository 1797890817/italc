/*
 * QtSlaveLauncher.cpp - class Ipc::QtSlaveLauncher providing mechanisms for
 *                       launching a slave application via QProcess
 *
 * Copyright (c) 2010 Tobias Doerffel <tobydox/at/users/dot/sf/dot/net>
 * Copyright (c) 2010 Univention GmbH
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

#include <QtCore/QProcess>

#include "Ipc/QtSlaveLauncher.h"

namespace Ipc
{

QtSlaveLauncher::QtSlaveLauncher( const QString &applicationFilePath ) :
	SlaveLauncher( applicationFilePath ),
	m_process( NULL )
{
}



QtSlaveLauncher::~QtSlaveLauncher()
{
	// base class destructor calls stop()
}



void QtSlaveLauncher::start( const QStringList &arguments )
{
	stop();
	m_process = new QProcess;
	m_process->start( applicationFilePath(), arguments );
}



void QtSlaveLauncher::stop()
{
	if( m_process )
	{
		if( !m_process->waitForFinished( 5000 ) )
		{
			m_process->terminate();
		}

		delete m_process;
	}
}



bool QtSlaveLauncher::isRunning() const
{
	return m_process && m_process->state() != QProcess::NotRunning;
}


}