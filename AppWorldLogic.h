/* Copyright (C) 2005-2021, UNIGINE. All rights reserved.
 *
 * This file is a part of the UNIGINE 2 SDK.
 *
 * Your use and / or redistribution of this software in source and / or
 * binary form, with or without modification, is subject to: (i) your
 * ongoing acceptance of and compliance with the terms and conditions of
 * the UNIGINE License Agreement; and (ii) your inclusion of this notice
 * in any version of this software that you use or redistribute.
 * A copy of the UNIGINE License Agreement is available by contacting
 * UNIGINE. at http://unigine.com/
 */


#ifndef __APP_WORLD_LOGIC_H__
#define __APP_WORLD_LOGIC_H__

#include <UnigineLogic.h>
#include <UnigineStreams.h>
#include <UnigineObjects.h>
#include <UniginePlayers.h>
#include "UnigineGame.h"
#include "UnigineEngine.h"
#include "UniginePrimitives.h"
#include <UnigineInput.h>
#include <UnigineConsole.h>
#include <vector>
#include <string>
#include "../source/CreatureHinge.h"
#include <stdlib.h>
#include <iostream>
#include "windows.h"
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <UnigineTimer.h>
#include <UnigineApp.h>

class AppWorldLogic : public Unigine::WorldLogic
{

public:
	AppWorldLogic();
	virtual ~AppWorldLogic();

	int init() override;
	int update() override;
	int postUpdate() override;
	int updatePhysics() override;
	int shutdown() override;
	int save(const Unigine::StreamPtr &stream) override;
	int restore(const Unigine::StreamPtr &stream) override;
	int getPositionFromDatabase();
	int transferPositionToDatabase();

private:

	Unigine::PlayerSpectatorPtr player;
	std::vector<CreatureHinge> creature;

	long long timeSent;
	long long timeRecieve;

	const std::string server = "";
	const std::string username = "";
	const std::string password = "";

	sql::Driver* driver;
	sql::Connection* con;
	sql::Statement* stmt_bodyPosition;
	sql::Statement* stmt_setPosition;
	sql::PreparedStatement* pstmt;
	sql::PreparedStatement* pstmt_change;
	sql::ResultSet* result;
	Unigine::Timer time;

	int id = 1;
	bool positionChanged = false;
};

#endif // __APP_WORLD_LOGIC_H__
