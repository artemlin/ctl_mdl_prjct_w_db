#include "CreatureHinge.h"


using namespace Unigine;
using namespace Unigine::Math;


CreatureHinge::CreatureHinge(int legs)
{
	if (legs % 2 == 0 && legs >= 4) {
		this->legsNumber = legs;
		for (int i = 0; i < this->legsNumber; i++)
		{
			_controlParams.push_back(0);
			_controlParams.push_back(0);
		}
		initZeroParams(legs);
	}
	else
	{
		Log::error("not enough legs during init\n");
	}
}

CreatureHinge::~CreatureHinge()
{
}

void CreatureHinge::initZeroParams(int legs)
{
	for (int i = 0; i < legs; i++)
	{
		sensorLegs.push_back(std::vector<vec3>());
		for (int j = 0; j < 9; j++)
		{
			sensorLegs.back().push_back(vec3(0, 0, 0));
		}

		_controlParams[2 * i] = 0;
		_controlParams[2 * i + 1] = 0;
	}

	sensorBody.push_back(vec3(0, 0, 0));
	sensorBody.push_back(vec3(0, 0, 0));
	sensorBody.push_back(vec3(0, 0, 0));


	double numberStates = 0;
}

void CreatureHinge::creatureConstructScale(const vec3& position, const float& scale)
{


	float lengthBody = 6.0f;

	body = createBodyBox("body", vec3(1.0f, lengthBody, 1.0f) * scale, 1000.0f, vec4(1.0f, 0.1f, 0.1f, 1.0f), Mat4(translate(0.0f, 0.0f, 2.7f * scale) * translate(position)));
	int legsNumber = 6;
	int halfLegsNumber = legsNumber / 2;
	float density = 0.90f;
	float yPosition = 0;
	float yHorizontalPos = 0;
	float lastLeg = 0;
	float _horizontalPrismaticDensity = 0.4;
	for (int i = 0; i < legsNumber; i++)
	{
		yPosition = lengthBody * density * (0.5f - 2.0f / (legsNumber - 2.0f) * (i % halfLegsNumber));
		if (i % halfLegsNumber < halfLegsNumber - 1) {
			lastLeg = 1;
		}
		else
		{
			lastLeg = -1;
		}
		yHorizontalPos = lengthBody * density * (0.5f - 2.0f / (legsNumber - 2.0f) * (i % halfLegsNumber)) - lengthBody * density / (halfLegsNumber - 1) * _horizontalPrismaticDensity * lastLeg;
		if (i < legsNumber / 2)
		{
			_legPart1.push_back(createBodyBox(("legPart1" + std::to_string(i)).c_str(), vec3(.6f, .1f, .1f) * scale, _massLegPart1, vec4(0.0f, 1.0f, 0.1f, 1.0f), Mat4(translate(-.5f * scale, yPosition * scale, 2.6f * scale) * translate(position))));
			_legPart2.push_back(createBodyBox(("legPart2" + std::to_string(i)).c_str(), vec3(1.5f, 0.2f, 0.2f) * scale, _massLegPart2, vec4(1.0f, 0.1f, 0.1f, 1.0f), Mat4(translate(-1.5f * scale, yPosition * scale, 2.6f * scale) * translate(position))));
			_legPart3.push_back(createBodyBox(("legPart3" + std::to_string(i)).c_str(), vec3(0.2f, 0.2f, 1.3f) * scale, _massLegPart3, vec4(1.0f, 0.1f, 0.1f, 1.0f), Mat4(translate(-2.5f * scale, yPosition * scale, 1.7f * scale) * translate(position))));

		}

		if (i >= legsNumber / 2)
		{
			_legPart1.push_back(createBodyBox(("legPart1" + std::to_string(i)).c_str(), vec3(.6f, .1f, .1f) * scale, _massLegPart1, vec4(0.0f, 1.0f, 0.1f, 1.0f), Mat4(translate(.5f * scale, yPosition * scale, 2.6f * scale) * translate(position))));
			_legPart2.push_back(createBodyBox(("legPart2" + std::to_string(i)).c_str(), vec3(1.5f, 0.2f, 0.2f) * scale, _massLegPart2, vec4(1.0f, 0.1f, 0.1f, 1.0f), Mat4(translate(1.5f * scale, yPosition * scale, 2.6f * scale) * translate(position))));
			_legPart3.push_back(createBodyBox(("legPart3" + std::to_string(i)).c_str(), vec3(0.2f, 0.2f, 1.3f) * scale, _massLegPart3, vec4(1.0f, 0.1f, 0.1f, 1.0f), Mat4(translate(2.5f * scale, yPosition * scale, 1.7f * scale) * translate(position))));
		}

	}

	for (int i = 0; i < legsNumber; i++)
	{

		yPosition = lengthBody * density * (0.5f - 2.0f / (legsNumber - 2.0f) * (i % halfLegsNumber));
		if (i % halfLegsNumber < halfLegsNumber - 1) {
			lastLeg = 1;
		}
		else
		{
			lastLeg = -1;
		}
		yHorizontalPos = lengthBody * density * (0.5f - 2.0f / (legsNumber - 2.0f) * (i % halfLegsNumber)) - lengthBody * density / (halfLegsNumber - 1) * _horizontalPrismaticDensity * lastLeg;

		if (i < legsNumber / 2)
		{
			_hingeVertical.push_back(createHingeJoint(body, _legPart1[i], Vec3(-0.0f, yPosition, 2.6f) * scale + position, vec3(0.0f, 1.0f, 0.0f)));
			_hingeHorizontal.push_back(createHingeJoint(_legPart2[i], _legPart1[i], Vec3(-.6f, yPosition, 2.6f) * scale + position, vec3(0.0f, 0.0f, 1.0f)));

			_fixedlegPart2ToLegPart3.push_back(createFixedJoint(_legPart2[i], _legPart3[i], Vec3(-2.5f, yPosition, 1.7f) * scale + position));
		}

		else
		{

			_hingeVertical.push_back(createHingeJoint(body, _legPart1[i], Vec3(0.0f, yPosition, 2.6f) * scale + position, vec3(0.0f, 1.0f, 0.0f)));
			_hingeHorizontal.push_back(createHingeJoint(_legPart2[i], _legPart1[i], Vec3(.6f, yPosition, 2.6f) * scale + position, vec3(0.0f, 0.0f, 1.0f)));
			_fixedlegPart2ToLegPart3.push_back(createFixedJoint(_legPart2[i], _legPart3[i], Vec3(2.5f, yPosition, 1.7f) * scale + position));
		}
	}

}





void CreatureHinge::destroy()
{
	body->deleteLater();
	body = nullptr;
	for (int i = 0; i < legsNumber; i++)
	{
		_legPart1[i]->deleteLater();
		_legPart2[i]->deleteLater();
		_legPart3[i]->deleteLater();
	}
	_hingeVertical.clear();
	_hingeHorizontal.clear();
	_fixedlegPart2ToLegPart3.clear();
	_legPart1.clear();
	_legPart2.clear();
	_legPart3.clear();

}

int CreatureHinge::isDestroyed()
{
	if (body == nullptr)
	{
		return 0;
	}
	return 1;
}

void CreatureHinge::getState()
{
	sensorBody[0] = body->getBodyLinearVelocity();
	sensorBody[1] = body->getWorldPosition();
	sensorBody[2] = body->getBodyAngularVelocity();
	numberStates++;
	std::cout << sensorBody[1].x << " " << sensorBody[1].y << " " << sensorBody[1].z << std::endl;

}



void CreatureHinge::setControl()
{
	int doubleLegsNumber = legsNumber * 2;
	if (_controlParams.size() == doubleLegsNumber)
	{
		for (int i = 0; i < legsNumber; i++)

		{
			      std::cout << _controlParams[2 * i + 1] << std::endl;
				_hingeVertical[i]->setAngularLimitFrom(_controlParams[2 * i+1]);
				_hingeVertical[i]->setAngularLimitTo(_controlParams[2 * i+1]);


				_hingeHorizontal[i]->setAngularLimitFrom(_controlParams[2 * i]);
				_hingeHorizontal[i]->setAngularLimitTo(_controlParams[2 * i]);

		}
	}

}

void CreatureHinge::resetControl()
{
	int doubleLegsNumber = legsNumber * 2;
	if (_controlParams.size() == doubleLegsNumber)
	{
		for (int i = 0; i < legsNumber; i++)
		{
			_hingeVertical[i]->setAngularLimitFrom(-90);
			_hingeVertical[i]->setAngularLimitTo(90);
			_hingeHorizontal[i]->setAngularLimitFrom(-90);
			_hingeHorizontal[i]->setAngularLimitTo(90);
		}
	}
}

