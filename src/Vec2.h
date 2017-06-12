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

	inline void		Normalize()										{ double length = GetLength(); if (IsPositive(length)) { mX /= length; mY /= length; } }

	inline double	Dot(const Vec2& rhs) const						{ return mX * rhs.mX + mY * rhs.mY; };

	inline Vec2		GetPerpendicular() const						{ return Vec2(-mY, mX); }

	inline double	GetDistance(const Vec2& rhs) const				{ return sqrt(GetDistanceSquared(rhs)); }
	inline double	GetDistanceSquared(const Vec2& rhs) const		{ return (rhs.mX - mX * rhs.mX - mX) + (rhs.mY - mY * rhs.mY - mY); }

	inline Vec2		GetReverse() const								{ return Vec2(-mX, -mY); }

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

