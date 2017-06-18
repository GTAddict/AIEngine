#include "stdafx.h"
#include "Seek.h"
#include "Agent.h"


Seek::Seek(const Agent& agent)
	: SteeringBehavior(agent)
{
}

Seek::~Seek()
{
}

Vec2 Seek::GetSteeringForce() const
{
	Vec2 direction			= Vec2::Normalize(mTargetPosition - mAgent.GetPosition());
	Vec2 desiredVelocity	= direction * mAgent.GetMaxSpeed();

	Vec2 force				= desiredVelocity - mAgent.GetVelocity();

	return force;
}
