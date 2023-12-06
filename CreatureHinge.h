#pragma once
#include <UnigineComponentSystem.h>
#include "UnigineGame.h"
#include "UnigineEngine.h"
#include "UniginePrimitives.h"
#include <UnigineObjects.h>
#include <UniginePhysics.h>
#include <UnigineWorlds.h>
#include <UnigineRender.h>
#include <UnigineViewport.h>
#include "vector"
#include "iostream"
#include "string"
#include "../source/Utils.h"




using namespace Unigine;
using namespace Utils;
using namespace Unigine::Math;


class CreatureHinge : public WorldLogic
{
public:
	CreatureHinge(int legs);
	~CreatureHinge();
	void initZeroParams(int legs);
	void creatureConstructScale(const vec3& position, const float& scale);
	void setControl();
	void destroy();
	int isDestroyed();
	void resetControl();
	void getState();

	std::vector<float> _controlParams;
	std::vector<float> _sensorParams;

	int legsNumber = 6;
	float numberStates = 0;

	std::vector<vec3> sensorBody;
	std::vector<std::vector<vec3>> sensorLegs;

	Unigine::ObjectMeshDynamicPtr body = nullptr;
	std::vector<Unigine::ObjectMeshDynamicPtr> _legPart1;
	std::vector<Unigine::ObjectMeshDynamicPtr> _legPart2;
	std::vector<Unigine::ObjectMeshDynamicPtr> _legPart3;


	std::vector<Unigine::JointHingePtr> _hingeVertical;
	std::vector<Unigine::JointHingePtr> _hingeHorizontal;
	std::vector<Unigine::JointFixedPtr> _fixedlegPart2ToLegPart3;

	float _massLegPart1 = 100;
	float _massLegPart2 = 100;
	float _massLegPart3 = 100;
	float _cubeMass = 50;
};
