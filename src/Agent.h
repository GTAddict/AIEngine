#pragma once
#include "MovingGameObject.h"

class World;

class Agent final : public MovingGameObject
{
public:
	Agent(World* world, const Vec2& position, double rotation, double boundingRadius, const Vec2& scale, double mass, const Vec2& velocity, double maxSpeed, double maxForce, double maxTurnRate);
	~Agent();

	virtual void Update(double deltaTime);
	virtual void Render();

	inline const World* GetWorld() { return mpWorld; }

private:

	World* mpWorld;
};

