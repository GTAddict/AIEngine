#pragma once
#include "SteeringBehavior.h"

class Flee : public SteeringBehavior
{
public:

					Flee(const Agent& agent);
					~Flee();

	virtual Vec2	GetSteeringForce() const override;
};

