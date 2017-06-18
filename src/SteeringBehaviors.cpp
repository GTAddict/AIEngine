#include "stdafx.h"
#include "SteeringBehaviors.h"
#include "Agent.h"

SteeringBehaviors::SteeringBehaviors(Agent* agent)
{
	mpAgent = agent;
}

SteeringBehaviors::~SteeringBehaviors()
{
}

Vec2 SteeringBehaviors::Seek(Vec2 targetPosition)
{
	Vec2 direction = Vec2::Normalize(targetPosition - mpAgent->GetPosition());
	Vec2 desiredVelocity = direction * mpAgent->GetMaxSpeed();

	Vec2 force = desiredVelocity - mpAgent->GetVelocity();

	return force;
}

Vec2 SteeringBehaviors::Flee(Vec2 targetPosition)
{
	Vec2 direction = Vec2::Normalize(mpAgent->GetPosition() - targetPosition);
	Vec2 desiredVelocity = direction * mpAgent->GetMaxSpeed();

	Vec2 force = desiredVelocity - mpAgent->GetVelocity();

	return force;
}

Vec2 SteeringBehaviors::Arrive(Vec2 targetPosition)
{
	return Vec2();
}

Vec2 SteeringBehaviors::Pursuit(Agent* target)
{
	return Vec2();
}

Vec2 SteeringBehaviors::Wander()
{
	return Vec2();
}

Vec2 SteeringBehaviors::ObstacleAvoidance(std::vector<GameObject*>& obstacles)
{
	return Vec2();
}

double SteeringBehaviors::ForwardComponent()
{
	return 0.0;
}

double SteeringBehaviors::SideComponent()
{
	return 0.0;
}

void SteeringBehaviors::SetTarget(const Vec2& target)
{
	mTarget = target;
}

void SteeringBehaviors::SetTargetAgent(Agent* agent)
{
	mpTargetAgent = agent;
}

Vec2 SteeringBehaviors::GetSteeringForce()
{
	return Vec2();
}
