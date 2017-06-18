#pragma once

#include "Vec2.h"

class Message;

class GameObject
{
public:

	GameObject();
	GameObject(const Vec2& position, const Vec2& scale, double boundingRadius);
	virtual ~GameObject();

	static int			NextValidId()							{ static int ID = 0; return ++ID; }	// Start IDs at 1.

	virtual void		Update(double deltaTime) = 0;
	virtual void		Render() = 0;
	virtual bool		HandleMessage(const Message& message);

	inline int			ID() const								{ return mID; };

	inline Vec2			GetPosition() const						{ return mPosition; }
	inline void			SetPosition(const Vec2& position)		{ mPosition = position; }

	inline double		GetBBRadius() const						{ return mBoundingRadius; }
	inline void			SetBBRadius(double radius)				{ mBoundingRadius = radius; }

	inline Vec2 		GetScale() const		 				{ return mScale; }
	inline void			SetScale(const Vec2& scale)				{ mBoundingRadius *= max(scale.mX, scale.mY) / max(mScale.mX, mScale.mY); mScale = scale; }
	inline void			SetScale(double scale)					{ mBoundingRadius *= scale / max(mScale.mX, mScale.mY); mScale = Vec2(scale, scale); }

protected:

	Vec2	mPosition;
	Vec2	mScale;
	double	mBoundingRadius;

private:

	int		mID;
};

