#include "stdafx.h"
#include "Agent.h"
#include "Cgdi.h"


Agent::Agent(World* world, const Vec2& position, double rotation, double boundingRadius, const Vec2& scale, double mass, const Vec2& velocity, double maxSpeed, double maxForce, double maxTurnRate)
	: MovingGameObject(position, Vec2(sin(rotation), -cos(rotation)), boundingRadius, scale, mass, velocity, maxSpeed, maxSpeed, maxTurnRate)
	, mpWorld(world)
{
}


Agent::~Agent()
{
}

void Agent::Update(double deltaTime)
{
	
}

void Agent::Render()
{
	gdi->RedBrush();
	gdi->Rect(mPosition.mX - 5, mPosition.mY - 5, mPosition.mX + 5, mPosition.mY + 5);
}
