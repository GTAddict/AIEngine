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
	float weightedSum = 0.0f;
	for (auto pair : mSteeringBehaviors)
	{
		weightedSum += pair.second->GetWeight();
	}

	// This is plain old summing for now.
	for (auto pair : mSteeringBehaviors)
	{
		SteeringForce += pair.second->GetSteeringForce() * pair.second->GetWeight() / weightedSum;
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
	double speed = mVelocity.GetLength();
	
	gdi->WhitePen();
	for (auto pair : mSteeringBehaviors)
	{
		gdi->Circle(pair.second->GetTarget(), mBoundingRadius);
	}

	Vec2 rightMostBottom;
	for (auto vertex : AgentTransform)
	{
		if (vertex.mX > rightMostBottom.mX) rightMostBottom.mX = vertex.mX;
		if (vertex.mY > rightMostBottom.mY) rightMostBottom.mY = vertex.mY;
	}

	std::string text = std::to_string(speed);
	for (auto pair : mSteeringBehaviors)
	{
		text += ", " + pair.second->GetName();
	}

	gdi->GreenPen();
	gdi->Line(mPosition, mPosition + mHeading * speed * 20);
	gdi->TextAtPos(rightMostBottom, text);

	gdi->RedPen();
	gdi->ClosedShape(AgentTransform);
}

void Agent::SeekTo(const Vec2& target)
{
	AddBehavior(static_cast<std::uint8_t>(SteeringBehavior::Type::Seek))->SetTarget(target);
}

void Agent::FleeFrom(const Vec2& target)
{
	AddBehavior(static_cast<std::uint8_t>(SteeringBehavior::Type::Flee))->SetTarget(target);
}

void Agent::ArriveAt(const Vec2& target)
{
	AddBehavior(static_cast<std::uint8_t>(SteeringBehavior::Type::Arrive))->SetTarget(target);
}

void Agent::StopSeek()
{
	RemoveBehavior(static_cast<std::uint8_t>(SteeringBehavior::Type::Seek));
}

void Agent::StopFlee()
{
	RemoveBehavior(static_cast<std::uint8_t>(SteeringBehavior::Type::Flee));
}

void Agent::StopArrive()
{
	RemoveBehavior(static_cast<std::uint8_t>(SteeringBehavior::Type::Arrive));
}

void Agent::SetTarget(const Vec2& target)
{
	for (auto pair : mSteeringBehaviors)
	{
		pair.second->SetTarget(target);
	}
}

// Returns the behavior associated with the type if one already exists,
// creates a new one otherwise.
SteeringBehavior* Agent::AddBehavior(std::uint8_t type, float weight)
{
	SteeringBehavior* behavior = nullptr;
	auto foundIt = mSteeringBehaviors.find(type);

	if (foundIt == mSteeringBehaviors.end())
	{
		behavior = SteeringBehavior::Create(static_cast<SteeringBehavior::Type>(type), *this);
		behavior->SetWeight(weight);
		mSteeringBehaviors[type] = behavior;
	}
	else
	{
		behavior = foundIt->second;
	}

	return behavior;
}

void Agent::RemoveBehavior(std::uint8_t type)
{
	auto foundIt = mSteeringBehaviors.find(type);

	if (foundIt != mSteeringBehaviors.end())
	{
		delete foundIt->second;
		mSteeringBehaviors.erase(foundIt);
	}
}