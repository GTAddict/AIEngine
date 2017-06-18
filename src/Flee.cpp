#include "stdafx.h"
#include "Flee.h"
#include "Agent.h"

Flee::Flee(const Agent& agent)
	: SteeringBehavior(agent)
{
}


Flee::~Flee()
{
}

Vec2 Flee::GetSteeringForce() const
{
	Vec2 direction			= Vec2::Normalize(mAgent.GetPosition() - mTargetPosition);
	Vec2 desiredVelocity	= direction * mAgent.GetMaxSpeed();

	Vec2 force				= desiredVelocity - mAgent.GetVelocity();

	return force;
}
