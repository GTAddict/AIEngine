#include "stdafx.h"
#include "Agent.h"
#include "Cgdi.h"
#include "SteeringBehaviors.h"
#include "Transformations.h"
#include "World.h"


Agent::Agent(World* world, const Vec2& position, double rotation, double boundingRadius, const Vec2& scale, double mass, const Vec2& velocity, double maxSpeed, double maxForce, double maxTurnRate)
	: MovingGameObject(position, Vec2(sin(rotation), -cos(rotation)), boundingRadius, scale, mass, velocity, maxSpeed, maxSpeed, maxTurnRate)
	, mpWorld(world)
{
	mVertices.push_back(Vec2(-1.0, 0.6));
	mVertices.push_back(Vec2(1.0, 0.0));
	mVertices.push_back(Vec2(-1.0, -0.6));

	mSteeringBehavior = new SteeringBehaviors(this);
}


Agent::~Agent()
{
	delete mSteeringBehavior;
}

void Agent::Update(double deltaTime)
{
	Vec2 SteeringForce = mSteeringBehavior->Seek(mTarget);
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
	 // gdi->WhitePen();
	 // gdi->Circle(mTarget, mBoundingRadius);
}
