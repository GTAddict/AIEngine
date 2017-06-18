#pragma 
#include "Vec2.h"
#include <vector>

class Agent;
class GameObject;

class SteeringBehaviors
{
	const double WanderRadius = 1.2;
	const double WanderDistance = 2.0;
	const double WanderJitterPerSec = 80.0;

public:
	SteeringBehaviors(Agent* agent);
	~SteeringBehaviors();

	Vec2 Seek(Vec2 targetPosition);
	Vec2 Flee(Vec2 targetPosition);
	Vec2 Arrive(Vec2 targetPosition);
	Vec2 Pursuit(Agent* target);
	Vec2 Wander();

	Vec2 ObstacleAvoidance(std::vector<GameObject*>& obstacles);

	double ForwardComponent();
	double SideComponent();

	void SetTarget(const Vec2& target);
	void SetTargetAgent(Agent* agent);

	Vec2 GetSteeringForce();

private:

	Agent* mpAgent;
	Agent* mpTargetAgent;

	Vec2 mSteeringForce;
	Vec2 mTarget;
	Vec2 mWanderTarget;


	double mDetectionBoxLength;

};

