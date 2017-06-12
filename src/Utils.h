#pragma once

#include <limits>
#include <cmath>

inline double LowestDouble()
{
	return std::numeric_limits<double>::lowest();
}

inline double Epsilon()
{
	return std::numeric_limits<double>::epsilon();
}

inline bool AreEqual(double a, double b)
{
	double difference = fabs(b - a);
	double epsilon = std::numeric_limits<float>::epsilon();

	return difference < epsilon && difference > -epsilon;
}

inline bool IsPositive(double x)
{
	return x > std::numeric_limits<float>::epsilon();
}