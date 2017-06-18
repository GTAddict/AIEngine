#pragma once
#include <cmath>
#include <vector>
#include "Vec2.h"

class Mat3
{
public:

	struct Matrix
	{
		double m11, m12, m13;
		double m21, m22, m23;
		double m31, m32, m33;

		Matrix()
			: m11(0.0), m12(0.0), m13(0.0)
			, m21(0.0), m22(0.0), m23(0.0)
			, m31(0.0), m32(0.0), m33(0.0)
		{
		}

		inline void Mul(const Matrix& rhs)
		{
			Matrix temp;

			temp.m11 = (m11 * rhs.m11) + (m12 * rhs.m21) + (m13 * rhs.m31);
			temp.m12 = (m11 * rhs.m12) + (m12 * rhs.m22) + (m13 * rhs.m32);
			temp.m13 = (m11 * rhs.m13) + (m12 * rhs.m23) + (m13 * rhs.m33);

			temp.m21 = (m21 * rhs.m11) + (m22 * rhs.m21) + (m23 * rhs.m31);
			temp.m22 = (m21 * rhs.m12) + (m22 * rhs.m22) + (m23 * rhs.m32);
			temp.m23 = (m21 * rhs.m13) + (m22 * rhs.m23) + (m23 * rhs.m33);

			temp.m31 = (m31 * rhs.m11) + (m32 * rhs.m21) + (m33 * rhs.m31);
			temp.m32 = (m31 * rhs.m12) + (m32 * rhs.m22) + (m33 * rhs.m32);
			temp.m33 = (m31 * rhs.m13) + (m32 * rhs.m23) + (m33 * rhs.m33);

			*this = temp;
		}
	};

	Mat3();
	~Mat3();

	inline void SetMatrix(const Matrix& rhs)
	{
		mMatrix = rhs;
	}

	inline void Identity()
	{
		mMatrix.m11 = 1.0;	mMatrix.m12 = 0.0;	mMatrix.m13 = 0.0;
		mMatrix.m21 = 0.0;	mMatrix.m22 = 1.0;	mMatrix.m23 = 0.0;
		mMatrix.m31 = 0.0;	mMatrix.m32 = 0.0;	mMatrix.m33 = 1.0;
	}

	inline void Translate(double x, double y)
	{
		Matrix matrix;

		matrix.m11 = 1.0;	matrix.m12 = 0.0;	matrix.m13 = 0.0;
		matrix.m21 = 0.0;	matrix.m22 = 1.0;	matrix.m23 = 0.0;
		matrix.m31 = x;		matrix.m32 = y;		matrix.m33 = 1.0;

		mMatrix.Mul(matrix);
	}

	inline void Scale(double x, double y)
	{
		Matrix matrix;

		matrix.m11 = x;		matrix.m12 = 0.0;	matrix.m13 = 0.0;
		matrix.m21 = 0.0;	matrix.m22 = y;		matrix.m23 = 0.0;
		matrix.m31 = 0.0;	matrix.m32 = 0.0;	matrix.m33 = 1.0;

		mMatrix.Mul(matrix);
	}

	inline void Rotate(double angle)
	{
		Matrix matrix;

		matrix.m11 = cos(angle);	matrix.m12 = sin(angle);	matrix.m13 = 0.0;
		matrix.m21 = -sin(angle);	matrix.m22 = cos(angle);	matrix.m23 = 0.0;
		matrix.m31 = 0.0;			matrix.m32 = 0.0;			matrix.m33 = 1.0;

		mMatrix.Mul(matrix);
	}

	inline void Rotate(const Vec2& forward, const Vec2& side)
	{
		Matrix matrix;

		matrix.m11 = forward.mX;	matrix.m12 = forward.mY;	matrix.m13 = 0.0;
		matrix.m21 = side.mX;		matrix.m22 = side.mY;		matrix.m23 = 0.0;
		matrix.m31 = 0.0;			matrix.m32 = 0.0;			matrix.m33 = 1.0;

		mMatrix.Mul(matrix);
	}

	inline void TransformVec2(std::vector<Vec2>& points)
	{
		for (auto& point : points)
		{
			TransformVec2(point);
		}
	}

	inline void TransformVec2(Vec2& point)
	{
		double x = mMatrix.m11 * point.mX + mMatrix.m21 * point.mY + mMatrix.m31;
		double y = mMatrix.m12 * point.mX + mMatrix.m22 * point.mY + mMatrix.m32;

		point.mX = x;
		point.mY = y;
	}

private:

	Matrix mMatrix;
};

