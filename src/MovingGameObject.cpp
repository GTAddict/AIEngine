#include "stdafx.h"
#include "MovingGameObject.h"

MovingGameObject::MovingGameObject(const Vec2& position, const Vec2& heading, double boundingRadius, const Vec2& scale, double mass, const Vec2& velocity, double maxSpeed, double maxForce, double maxTurnRate)
	: GameObject(position, scale, boundingRadius)
	, mMass(mass)
	, mVelocity(velocity)
	, mHeading(heading)
	, mMaxSpeed(maxSpeed)
	, mMaxForce(maxForce)
	, mMaxTurnRate(mMaxTurnRate)
{
}


MovingGameObject::~MovingGameObject()
{
}