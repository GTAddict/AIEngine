#pragma once
#include "SteeringBehavior.h"

class Arrive : public SteeringBehavior
{
public:

					Arrive(const Agent& agent);
					~Arrive();

	virtual Vec2	GetSteeringForce() const override;
	void			SetDecelerationFactor(double decelerationFactor);

private:
	
	double			mDecelerationFactor;
};

