#pragma once
#include "MovingGameObject.h"
#include "Vec2.h"
#include <vector>

class World;
class SteeringBehaviors;

class Agent final : public MovingGameObject
{
public:
	Agent(World* world, const Vec2& position, double rotation, double boundingRadius, const Vec2& scale, double mass, const Vec2& velocity, double maxSpeed, double maxForce, double maxTurnRate);
	~Agent();

	virtual void Update(double deltaTime);
	virtual void Render();

	inline const World* GetWorld() { return mpWorld; }

	inline void SetTarget(Vec2 target) { mTarget = target; }

private:

	World* mpWorld;
	std::vector<Vec2> mVertices;
	SteeringBehaviors* mSteeringBehavior;
	Vec2 mTarget;
};

