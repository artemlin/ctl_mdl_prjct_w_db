#include "../source/Utils.h"
#include <random>
#include <iostream>
#include <sstream>
#include <UnigineGame.h>
#include <filesystem>
using namespace Unigine;

namespace Utils {



	ObjectMeshDynamicPtr createBodyBox(const char* name, const Unigine::Math::vec3& size, float mass, const Unigine::Math::Vec4& color, const Unigine::Math::mat4& transform)
	{

		ObjectMeshDynamicPtr OMD = Primitives::createBox(size);
		OMD->setWorldTransform(transform);
		OMD->setMaterialParameterFloat4("albedo_color", color, 0);
		OMD->setCollision(1, 0);
		BodyRigidPtr body = BodyRigid::create(OMD);
		ShapePtr shape = ShapeBox::create(size);
		body->addShape(shape, translate(Unigine::Math::vec3(0.0f)));
		OMD->getBody()->getShape(0)->setMass(mass);
		return OMD;
	}


	JointHingePtr createHingeJoint(ObjectMeshDynamicPtr body1, ObjectMeshDynamicPtr body2, const Unigine::Math::vec3& transform, const Unigine::Math::vec3& axis)
	{
		JointHingePtr hingeJoint;
		hingeJoint = JointHinge::create(body1->getBody(), body2->getBody(), transform, axis);
		hingeJoint->setNumIterations(16);
		hingeJoint->setAngularRestitution(0.1);
		hingeJoint->setLinearRestitution(0.1);
		return hingeJoint;
	}



	JointFixedPtr createFixedJoint(ObjectMeshDynamicPtr body1, ObjectMeshDynamicPtr body2, const Unigine::Math::vec3& transform)
	{
		JointFixedPtr fixedJoint;
		fixedJoint = JointFixed::create(body1->getBody(), body2->getBody(), transform);
		fixedJoint->setNumIterations(16);
		fixedJoint->setAngularRestitution(0.1);
		fixedJoint->setLinearRestitution(0.1);
		return fixedJoint;
	}


}
