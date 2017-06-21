#include "stdafx.h"
#include "Arrive.h"
#include "Agent.h"
#include "Seek.h"

const double DefaultDecelerationFactor = 10.0f;
const double DefaultBrakeRadius = 100.0f;

Arrive::Arrive(const Agent& agent)
	: SteeringBehavior(agent)
	, mDecelerationFactor(DefaultDecelerationFactor)
{
	mName = "Arrive";
}

Arrive::~Arrive()
{
}

Vec2 Arrive::GetSteeringForce() const
{
	Vec2 force				= SteeringBehavior::GetSteeringForce();

	Vec2 vecToTarget		= mTargetPosition - mAgent.GetPosition();
	double distance			= vecToTarget.GetLength();

	if (distance > DefaultBrakeRadius)
	{
		Vec2 direction = Vec2::Normalize(mTargetPosition - mAgent.GetPosition());
		Vec2 desiredVelocity = direction * mAgent.GetMaxSpeed();

		force += desiredVelocity - mAgent.GetVelocity();

	}
	else if (distance > 0.0f)
	{
		double speed = distance / mDecelerationFactor;

		speed = min(speed, mAgent.GetMaxSpeed());

		Vec2 desiredVelocity = Vec2::Normalize(vecToTarget) * speed;

		force += desiredVelocity - mAgent.GetVelocity();
	}

	return force;
}

void Arrive::SetDecelerationFactor(double decelerationFactor)
{
	mDecelerationFactor = decelerationFactor;
}
