#pragma once

#include <limits>
#include <cmath>

double LowestDouble()
{
	return std::numeric_limits<double>::lowest();
}

double Epsilon()
{
	return std::numeric_limits<double>::epsilon();
}

bool AreEqual(double a, double b)
{
	double difference = fabs(b - a);
	double epsilon = std::numeric_limits<float>::epsilon();

	return difference < epsilon && difference > -epsilon;
}

bool IsPositive(double x)
{
	return x > std::numeric_limits<float>::epsilon();
}