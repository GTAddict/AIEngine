#pragma once
#include "SteeringBehavior.h"

class Seek : public SteeringBehavior
{
public:

					Seek(const Agent& agent);
					~Seek();

	virtual Vec2	GetSteeringForce() const override;
};

