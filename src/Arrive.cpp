#include "stdafx.h"
#include "Arrive.h"
#include "Agent.h"

const double DefaultDecelerationFactor = 10.0f;

Arrive::Arrive(const Agent& agent)
	: SteeringBehavior(agent)
	, mDecelerationFactor(DefaultDecelerationFactor)
{
}

Arrive::~Arrive()
{
}

Vec2 Arrive::GetSteeringForce() const
{
	Vec2 force				= SteeringBehavior::GetSteeringForce();

	Vec2 vecToTarget		= mTargetPosition - mAgent.GetPosition();
	double distance			= vecToTarget.GetLength();

	if (!AreEqual(distance, 0.0f))
	{
		double speed = distance / distance;// / mDecelerationFactor;

		speed = min(speed, mAgent.GetMaxSpeed());

		Vec2 desiredVelocity = vecToTarget * speed / distance ;

		force += desiredVelocity - mAgent.GetVelocity();
	}

	return force;
}

void Arrive::SetDecelerationFactor(double decelerationFactor)
{
	mDecelerationFactor = decelerationFactor;
}
