#pragma once

#include "Vec2.h"
#include "GameObject.h"
#include <assert.h>

class MovingGameObject : public GameObject
{
public:

	MovingGameObject(const Vec2& position, const Vec2& heading, double boundingRadius, const Vec2& scale, double mass, const Vec2& velocity, double maxSpeed, double maxForce, double maxTurnRate);
	virtual ~MovingGameObject();

	inline double	GetMass()								{ return mMass; }

	inline const	Vec2& GetVelocity() const				{ return mVelocity; }
	inline void		SetVelocity(const Vec2& velocity)		{ mVelocity = velocity; }

	inline double	GetMaxSpeed() const						{ return mMaxSpeed; }
	inline void		SetMaxSpeed(double maxSpeed)			{ mMaxSpeed = maxSpeed; }

	inline double	GetMaxForce() const						{ return mMaxForce; }
	inline void		SetMaxForce(double maxForce)			{ mMaxForce = maxForce; }

	inline double	GetMaxTurnRate() const					{ return mMaxTurnRate; }
	inline void		SetMaxTurnRate(double maxTurnRate)		{ mMaxTurnRate = maxTurnRate; }

	inline double	GetSpeed() const						{ return mVelocity.GetLength(); }
	inline double	GetSpeedSquared() const					{ return mVelocity.GetLengthSquared(); }
	inline bool		IsSpeedMax() const						{ double maxSpeedSq = mMaxSpeed * mMaxSpeed; return maxSpeedSq > GetSpeedSquared() || AreEqual(maxSpeedSq, GetSpeedSquared()); }

	inline const	Vec2& GetHeading() const				{ return mHeading; }
	inline void		SetHeading(const Vec2& heading)			{ assert(!AreEqual(heading.GetLengthSquared(), 0.0)); mHeading = heading; mSide = heading.GetPerpendicular(); }
	inline bool		Face(const Vec2& direction)				{ assert(false); return false; } // Unimplemented!!

	inline const	Vec2& GetSide() const					{ return mSide; }

protected:

	Vec2 mVelocity;
	Vec2 mHeading;
	Vec2 mSide;

	double mMass;
	double mMaxSpeed;
	double mMaxForce;
	double mMaxTurnRate;
};