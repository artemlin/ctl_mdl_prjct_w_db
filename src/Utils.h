#pragma once
#include <vector>
#include "UniginePrimitives.h"
#include <UnigineObjects.h>
#include <fstream>
#include <UnigineLogic.h>
#include <UnigineStreams.h>
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


using namespace Unigine;
namespace Utils {

	Unigine::JointHingePtr createHingeJoint(ObjectMeshDynamicPtr body1, ObjectMeshDynamicPtr body2, const Unigine::Math::vec3& transform, const Unigine::Math::vec3& axis);
	Unigine::ObjectMeshDynamicPtr createBodyBox(const char* name, const Unigine::Math::vec3& size, float mass, const Unigine::Math::Vec4& color, const Unigine::Math::mat4& transform);
	Unigine::JointFixedPtr createFixedJoint(ObjectMeshDynamicPtr body1, ObjectMeshDynamicPtr body2, const Unigine::Math::vec3& transform);
   	
}
