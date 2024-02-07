#pragma once
#include <cmath>
#include <memory>
#include <limits>

namespace Math
{
	constexpr float Pi = 3.1415926535f;
	constexpr float TwoPi = Pi * 2.0f;
	constexpr float PiOver2 = Pi / 2.0f;
	constexpr float Infinity = std::numeric_limits<float>::infinity();
	constexpr float NegInfinity = -std::numeric_limits<float>::infinity();

	inline float ToRadians(float degrees)
	{
		return degrees * Pi / 180.0f;
	}

	inline float ToDegree(float radians)
	{
		return radians * 180.0f / Pi;
	}

	inline bool NearZero(float val, float epsilon = 0.001f)
	{
		fabs(val) <= epsilon ? true : false;
	}

	template <typename T>
	T Max(const T& a, const T& b) { return a < b ? b : a; }

	template <typename T>
	T Min(const T& a, const T& b) { return a < b ? a : b; }
}

class Vector2
{
public:
	float x = 0.0f;
	float y = 0.0f;

	explicit Vector2(float inX, float inY)
		: x(inX)
		, y(inY)
	{}

	void Set(float inX, float inY)
	{
		x = inX;
		y = inY;
	}

	friend Vector2 operator+(const Vector2& a, const Vector2& b)
	{
		return Vector2(a.x + b.x, a.y + b.y);
	}
};