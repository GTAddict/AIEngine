#pragma once

class Vec2 final
{
public:
	
	Vec2();
	Vec2(double x, double y);
	~Vec2();

	inline void Zero();
	inline bool IsZero() const;

	inline double GetLength() const;
	inline double GetLengthSquared() const;

	inline void Normalize();

	inline double Dot(const Vec2& rhs) const;

	inline Vec2 GetPerpendicular() const;

	inline double GetDistance(const Vec2& rhs) const;
	inline double GetDistanceSquared(const Vec2& rhs) const;

	inline Vec2 GetReverse() const;

	const Vec2& operator+=(const Vec2& rhs);
	const Vec2& operator-=(const Vec2& rhs);
	const Vec2& operator*=(const double rhs);
	const Vec2& operator/=(const double rhs);

	bool operator==(const Vec2& rhs);
	bool operator!=(const Vec2& rhs);

private:

	double mX;
	double mY;
};

