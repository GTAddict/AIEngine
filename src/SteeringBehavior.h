#pragma once
#include "Vec2.h"
#include <vector>
#include <map>

class Agent;
class GameObject;

class SteeringBehavior
{

public:

	enum class Type : std::uint8_t
	{
		Invalid = 0,
		Start = 1,
		Seek = Start,
		Flee,
		Arrive,
		Count
	};
	
								SteeringBehavior(const Agent& agent);
	virtual						~SteeringBehavior();

	virtual Vec2				GetSteeringForce() const;

	void						SetTarget(const Vec2& target);
	const Vec2&					GetTarget();
	
	static SteeringBehavior*	Create(Type type, const Agent& agent);

	virtual const std::string&	GetName() const { return mName; }

	void						AddBehavior(Type type, const Agent& agent, float weight);
	void						SetWeight(float weight) { mWeight = weight; }
	float						GetWeight() const { return mWeight; }

protected:

	const Agent&										mAgent;
	Vec2												mTargetPosition;
	std::map<SteeringBehavior::Type, SteeringBehavior*> mChildBehaviors;
	std::string											mName;
	float												mWeight;
};

