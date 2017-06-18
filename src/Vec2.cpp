#include "stdafx.h"
#include "Vec2.h"
#include <math.h>


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

const Vec2& Vec2::operator/=(double rhs)
{
	mX /= rhs;
	mY /= rhs;

	return *this;
}

const Vec2& Vec2::operator+(const Vec2& rhs)
{
	return *this += rhs;
}

const Vec2& Vec2::operator-(const Vec2& rhs)
{
	return *this -= rhs;
}

const Vec2& Vec2::operator*(double rhs)
{
	return *this *= rhs;
}

const Vec2& Vec2::operator/(double rhs)
{
	return *this /= rhs;
}

bool Vec2::operator==(const Vec2 & rhs)
{
	return AreEqual(mX, rhs.mX) && AreEqual(mY, rhs.mY);
}

bool Vec2::operator!=(const Vec2 & rhs)
{
	return !(*this == rhs);
}

