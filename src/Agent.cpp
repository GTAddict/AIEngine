#include "stdafx.h"
#include "Agent.h"
#include "Cgdi.h"
#include "SteeringBehavior.h"
#include "Seek.h"
#include "Flee.h"
#include "Transformations.h"
#include "World.h"


Agent::Agent(World* world, const Vec2& position, double rotation, double boundingRadius, const Vec2& scale, double mass, const Vec2& velocity, double maxSpeed, double maxForce, double maxTurnRate)
	: MovingGameObject(position, Vec2(sin(rotation), -cos(rotation)), boundingRadius, scale, mass, velocity, maxSpeed, maxSpeed, maxTurnRate)
	, mpWorld(world)
{
	mVertices.push_back(Vec2(-1.0, 0.6));
	mVertices.push_back(Vec2(1.0, 0.0));
	mVertices.push_back(Vec2(-1.0, -0.6));
}


Agent::~Agent()
{
	for (auto pair : mSteeringBehaviors)
	{
		delete pair.second;
	}
}

void Agent::Update(double deltaTime)
{
	Vec2 SteeringForce;

	// This is plain old summing for now.
	for (auto pair : mSteeringBehaviors)
	{
		SteeringForce += pair.second->GetSteeringForce();
	}

	Vec2 Acceleration = SteeringForce / mMass;

	mVelocity += Acceleration * deltaTime;
	mVelocity.Truncate(GetMaxSpeed());

	mPosition += mVelocity;

	mPosition.WrapAround(Vec2(mpWorld->GetClientWidth(), mpWorld->GetClientHeight()));

	if (IsPositive(mVelocity.GetLengthSquared()))
	{
		mHeading = Vec2::Normalize(mVelocity);
		mSide = mHeading.GetPerpendicular();
	}
}

void Agent::Render()
{
	Vec2 heading = GetHeading();

	std::vector<Vec2> AgentTransform = WorldTransform(mVertices, GetPosition(), heading, GetSide(), GetScale());
	gdi->RedPen();
	gdi->ClosedShape(AgentTransform);
	//gdi->ClosedShape(mVertices);
	 // gdi->Circle(mPosition, mBoundingRadius);
	 gdi->WhitePen();
	 for (auto pair : mSteeringBehaviors)
	 {
		 gdi->Circle(pair.second->GetTarget(), mBoundingRadius);
	 }
}

void Agent::SeekTo(const Vec2& target)
{
	AddBehavior(static_cast<std::uint8_t>(SteeringBehavior::Type::Seek))->SetTarget(target);
}

void Agent::FleeFrom(const Vec2& target)
{
	AddBehavior(static_cast<std::uint8_t>(SteeringBehavior::Type::Flee))->SetTarget(target);
}

// Returns the behavior associated with the type if one already exists,
// creates a new one otherwise.
SteeringBehavior* Agent::AddBehavior(std::uint8_t type)
{
	SteeringBehavior* behavior = nullptr;
	auto foundIt = mSteeringBehaviors.find(type);

	if (foundIt == mSteeringBehaviors.end())
	{
		behavior = SteeringBehavior::Create(static_cast<SteeringBehavior::Type>(type), *this);
		mSteeringBehaviors[type] = behavior;
	}
	else
	{
		behavior = foundIt->second;
	}

	return behavior;
}


