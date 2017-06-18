#include "stdafx.h"
#include "SteeringBehavior.h"
#include "Seek.h"
#include "Flee.h"

SteeringBehavior::SteeringBehavior(const Agent& agent)
	: mAgent(agent)
{
}

SteeringBehavior::~SteeringBehavior()
{
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
	case SteeringBehavior::Type::Seek:	return new Seek(agent);
		break;
	case SteeringBehavior::Type::Flee:	return new Flee(agent);
		break;
	default:							return nullptr;
		break;
	}
}
