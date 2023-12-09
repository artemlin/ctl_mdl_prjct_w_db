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


#include "AppWorldLogic.h"

// World logic, it takes effect only when the world is loaded.
// These methods are called right after corresponding world script's (UnigineScript) methods.

AppWorldLogic::AppWorldLogic()
{
}

AppWorldLogic::~AppWorldLogic()
{
}


int AppWorldLogic::getPositionFromDatabase()
{

	sql::ResultSet* result;
	pstmt = con->prepareStatement("SELECT*  FROM setPosition ORDER BY id DESC LIMIT 1 ");
	result = pstmt->executeQuery();
	std::cout << result << std::endl;
	while(result->next())
	{
		if (result->getBoolean(14) == false && result->getInt(1) != NULL)
		{
			for (int i = 0; i < 12; i++)
			{
				if (!result->isNull(i + 2))
				{
					std::cout << result->getDouble(i + 2) << std::endl;
					creature[0]._controlParams[i] = result->getDouble(i + 2);
					positionChanged = true;
				}

			}
			creature[0].setControl();
		}
		pstmt = con->prepareStatement("UPDATE setPosition SET done = true WHERE id = ?");
		pstmt->setInt(1, result->getInt(1));
		pstmt->executeQuery();
		printf("Row updated\n");
	}
	delete result;
	return 0;
}



int AppWorldLogic::transferPositionToDatabase()
{ 
	pstmt = con->prepareStatement("INSERT INTO bodyPosition(bodyX , bodyY , bodyZ ) VALUES(?,?,?)");
	pstmt->setDouble(1, creature[0].sensorBody[1].x);
	pstmt->setDouble(2, creature[0].sensorBody[1].y);
	pstmt->setDouble(3, creature[0].sensorBody[1].z);
	pstmt->execute();
	std::cout << "One row inserted." << std::endl;
	return 0;
}





int AppWorldLogic::init()
{
	App::setBackgroundUpdate(1);
	// setting up physics parameters
	Physics::setGravity(vec3(0.0f, 0.0f, -9.8f * 2.0f));
	Physics::setFrozenLinearVelocity(0.01f);
	Physics::setFrozenAngularVelocity(0.01f);
	Physics::setNumIterations(8);

	// setting up player
	player = PlayerSpectator::create();

	player->setPosition(Vec3(0.0f, -5.0f, 1.0f));
	player->setDirection(vec3(0.0f, 0.0f, 0.0f), vec3(0.0f, 0.0f, 0.0f));
	Game::setPlayer(player);

	vec3 position = vec3(0.0, 0.0, 0.0);
	vec3 position1 = vec3(100.0, 0.0, 10.0);

	for (int i = 0; i < 1; i++)
	{
		creature.push_back(CreatureHinge(6));
	}
	try
	{
		driver = get_driver_instance();
		con = driver->connect(server, username, password);
	}
	catch (sql::SQLException e)
	{
		std::cout << "Could not connect to server. Error message: " << e.what() << std::endl;
		system("pause");
		exit(1);
	}
	con->setSchema("logsdata");

	stmt_setPosition = con->createStatement();
	stmt_setPosition->execute("DROP TABLE IF EXISTS bodyPosition");
	std::cout << "Finished dropping table (if existed)" << std::endl;
	stmt_setPosition->execute("CREATE TABLE bodyPosition (id serial NOT NULL PRIMARY KEY, bodyX FLOAT, bodyY FLOAT , bodyZ FLOAT);");
	std::cout << "Finished creating table" << std::endl;


	stmt_setPosition = con->createStatement();
	stmt_setPosition->execute("DROP TABLE IF EXISTS setPosition");
	std::cout << "Finished dropping table (if existed)" << std::endl;
	stmt_setPosition->execute("CREATE TABLE setPosition (id serial NOT NULL PRIMARY KEY, 1_horizontal FLOAT DEFAULT NULL, 1_vertical FLOAT \
                                                                             , 2_horizontal FLOAT, 2_vertical FLOAT \
                                                                             , 3_horizontal FLOAT, 3_vertical FLOAT \
	                                                                         , 4_horizontal FLOAT, 4_vertical FLOAT \
                                                                             , 5_horizontal FLOAT, 5_vertical FLOAT  \
		                                                                     , 6_horizontal FLOAT, 6_vertical FLOAT \
                                                                             , done boolean DEFAULT false );");
	std::cout << "Finished creating table" << std::endl; 

	timeRecieve = time.getTime();
	timeSent = time.getTime() + 500000;
	std::cout << timeRecieve << std::endl;
	creature[0].creatureConstructScale(position, 5);
	return 1;
}

////////////////////////////////////////////////////////////////////////////////
// start of the main loop
////////////////////////////////////////////////////////////////////////////////

int AppWorldLogic::update()
{
	Unigine::Math::vec3 position = Unigine::Math::vec3(0.0, 0.0, 0.0);
	if (Input::isKeyDown(Input::KEY_C)) {
		if (creature[0].isDestroyed())
		{
			creature[0].destroy();
		}
		creature[0].creatureConstructScale(position, 5);
		for (int i = 0; i < 12; i++)
		{
			creature[0]._controlParams[i] = 0;
			positionChanged = true;
		}
		creature[0].setControl();
	}

	if (Input::isKeyDown(Input::KEY_X)) {
		creature[0].getState();
		transferPositionToDatabase();
	}

	if (time.getTime() - timeSent > 5000000 && positionChanged) {
		creature[0].getState();
		transferPositionToDatabase();
		timeSent = time.getTime();
	}

	if (time.getTime() - timeRecieve > 5000000) {
		getPositionFromDatabase();
		timeRecieve = time.getTime();
	}
	// Write here code to be called before updating each render frame: specify all graphics-related functions you want to be called every frame while your application executes.
	return 1;
}

int AppWorldLogic::postUpdate()
{
	// The engine calls this function after updating each render frame: correct behavior after the state of the node has been updated.
	return 1;
}

int AppWorldLogic::updatePhysics()
{
	// Write here code to be called before updating each physics frame: control physics in your application and put non-rendering calculations.
	// The engine calls updatePhysics() with the fixed rate (60 times per second by default) regardless of the FPS value.
	// WARNING: do not create, delete or change transformations of nodes here, because rendering is already in progress.
	return 1;
}

////////////////////////////////////////////////////////////////////////////////
// end of the main loop
////////////////////////////////////////////////////////////////////////////////

int AppWorldLogic::shutdown()
{
	// Write here code to be called on world shutdown: delete resources that were created during world script execution to avoid memory leaks.
	return 1;
}

int AppWorldLogic::save(const Unigine::StreamPtr &stream)
{
	// Write here code to be called when the world is saving its state (i.e. state_save is called): save custom user data to a file.
	UNIGINE_UNUSED(stream);
	return 1;
}

int AppWorldLogic::restore(const Unigine::StreamPtr &stream)
{
	// Write here code to be called when the world is restoring its state (i.e. state_restore is called): restore custom user data to a file here.
	UNIGINE_UNUSED(stream);
	return 1;
}
