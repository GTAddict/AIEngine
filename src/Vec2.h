#pragma once

class Vec2 final
{
public:
	
	Vec2();
	Vec2(double x, double y);
	~Vec2();

	inline void		Zero()											{ mX = 0; mY = 0; }
	inline bool		IsZero() const									{ return ((mX * mX) + (mY * mY)) < LowestDouble(); }

	inline double	GetLength() const								{ return sqrt(GetLengthSquared()); }
	inline double	GetLengthSquared() const						{ return (mX * mX) + (mY * mY); }

	inline void		Normalize()										{ *this = Vec2::Normalize(*this); }
	static Vec2		Normalize(Vec2 vector)							{ double length = vector.GetLength(); if (IsPositive(length)) { vector.mX /= length; vector.mY /= length; } return vector; }

	inline double	Dot(const Vec2& rhs) const						{ return mX * rhs.mX + mY * rhs.mY; };

	inline Vec2		GetPerpendicular() const						{ return Vec2(-mY, mX); }

	inline double	GetDistance(const Vec2& rhs) const				{ return sqrt(GetDistanceSquared(rhs)); }
	inline double	GetDistanceSquared(const Vec2& rhs) const		{ return (rhs.mX - mX * rhs.mX - mX) + (rhs.mY - mY * rhs.mY - mY); }

	inline Vec2		GetReverse() const								{ return Vec2(-mX, -mY); }

	inline Vec2		Truncate(double max)							{ if (GetLengthSquared() > max * max) { Normalize(); *this *= max; } return *this; }

	inline void		WrapAround(Vec2 screenBounds)					{ while (mX >= screenBounds.mX) mX -= screenBounds.mX; while (mY >= screenBounds.mY) mY -= screenBounds.mY; }

	const Vec2&		operator+=(const Vec2& rhs);
	const Vec2&		operator-=(const Vec2& rhs);
	const Vec2&		operator*=(const double rhs);
	const Vec2&		operator/=(const double rhs);

	const Vec2&		operator+(const Vec2& rhs);
	const Vec2&		operator-(const Vec2& rhs);
	const Vec2&		operator*(double rhs);
	const Vec2&		operator/(double rhs);

	bool			operator==(const Vec2& rhs);
	bool			operator!=(const Vec2& rhs);

	double mX;
	double mY;
};

