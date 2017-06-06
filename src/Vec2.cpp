#include "stdafx.h"
#include "Vec2.h"
#include <math.h>
#include "Utils.h"


Vec2::Vec2()
	: mX(0.0)
	, mY(0.0)
{
}

Vec2::Vec2(double x, double y)
	: mX(x)
	, mY(y)
{
}


Vec2::~Vec2()
{
}

inline void Vec2::Zero()
{
	mX = 0;
	mY = 0;
}

inline bool Vec2::IsZero() const
{
	return ((mX * mX) + (mY * mY)) < LowestDouble();
}

inline double Vec2::GetLength() const
{
	return sqrt(GetLengthSquared());
}

inline double Vec2::GetLengthSquared() const
{
	return (mX * mX) + (mY * mY);
}

inline void Vec2::Normalize()
{
	double length = GetLength();

	if (IsPositive(length))
	{
		mX /= length;
		mY /= length;
	}
}

inline double Vec2::Dot(const Vec2 & rhs) const
{
	return mX * rhs.mX + mY * rhs.mY;
}

inline Vec2 Vec2::GetPerpendicular() const
{
	return Vec2(mX, -mY);
}

inline double Vec2::GetDistance(const Vec2& rhs) const
{
	return sqrt(GetDistanceSquared(rhs));
}

inline double Vec2::GetDistanceSquared(const Vec2& rhs) const
{
	return (rhs.mX - mX * rhs.mX - mX) + (rhs.mY - mY * rhs.mY - mY);
}

inline Vec2 Vec2::GetReverse() const
{
	return Vec2(-mX, -mY);
}

const Vec2& Vec2::operator+=(const Vec2& rhs)
{
	mX += rhs.mX;
	mY += rhs.mY;

	return *this;
}

const Vec2& Vec2::operator-=(const Vec2& rhs)
{
	mX -= rhs.mX;
	mY -= rhs.mY;

	return *this;
}

const Vec2& Vec2::operator*=(double rhs)
{
	mX *= rhs;
	mY *= rhs;

	return *this;
}

const Vec2 & Vec2::operator/=(double rhs)
{
	mX /= rhs;
	mY /= rhs;

	return *this;
}

bool Vec2::operator==(const Vec2 & rhs)
{
	return AreEqual(mX, rhs.mX) && AreEqual(mY, rhs.mY);
}

bool Vec2::operator!=(const Vec2 & rhs)
{
	return !(*this == rhs);
}

