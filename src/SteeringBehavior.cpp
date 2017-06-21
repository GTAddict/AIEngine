#include "stdafx.h"
#include "SteeringBehavior.h"
#include "Seek.h"
#include "Flee.h"
#include "Arrive.h"

SteeringBehavior::SteeringBehavior(const Agent& agent)
	: mAgent(agent)
{
}

SteeringBehavior::~SteeringBehavior()
{
}

Vec2 SteeringBehavior::GetSteeringForce() const
{
	// Naive summing for now.
	Vec2 totalForce;
	for (auto behavior : mChildBehaviors)
	{
		totalForce += behavior.second->GetSteeringForce();
	}
	return totalForce;
}

void SteeringBehavior::SetTarget(const Vec2& target)
{
	mTargetPosition = target;
}

const Vec2& SteeringBehavior::GetTarget()
{
	return mTargetPosition;
}

SteeringBehavior* SteeringBehavior::Create(Type type, const Agent& agent)
{
	switch (type)
	{
	case SteeringBehavior::Type::Seek:		return new Seek(agent);
		break;
	case SteeringBehavior::Type::Flee:		return new Flee(agent);
		break;
	case SteeringBehavior::Type::Arrive:	return new Arrive(agent);
		break;
	default:								return nullptr;
		break;
	}
}

void SteeringBehavior::AddBehavior(Type type, const Agent& agent)
{
	auto foundIt = mChildBehaviors.find(type);
	if (foundIt != mChildBehaviors.end())
	{
		mChildBehaviors[type] = Create(type, agent);
	}
}
