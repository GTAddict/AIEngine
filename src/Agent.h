#pragma once
#include "MovingGameObject.h"
#include "Vec2.h"
#include <vector>
#include <map>

class World;
class SteeringBehavior;

class Agent final : public MovingGameObject
{
public:
	Agent(World* world, const Vec2& position, double rotation, double boundingRadius, const Vec2& scale, double mass, const Vec2& velocity, double maxSpeed, double maxForce, double maxTurnRate);
	~Agent();

	virtual void Update(double deltaTime);
	virtual void Render();

	inline const World* GetWorld() { return mpWorld; }

	void SeekTo(const Vec2& target);
	void FleeFrom(const Vec2& target);

private:

	SteeringBehavior* AddBehavior(std::uint8_t type);

	World* mpWorld;
	std::vector<Vec2> mVertices;

	// Currently we're going to allow only one instance of each type of behavior
	// to be available. We can change the design if required later.
	std::map<std::uint8_t, SteeringBehavior*> mSteeringBehaviors;
};

