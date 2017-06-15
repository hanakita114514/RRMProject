#pragma once
#include <math.h>
struct Vector2
{
	float x, y;

	Vector2() : x(0),y(0)
	{

	}

	Vector2(float fx, float fy) : x(fx), y(fy)
	{

	}

	void operator += (const Vector2 v)
	{
		x += v.x;
		y += v.y;
	}

	void operator -= (const Vector2 v)
	{
		x -= v.x;
		y -= v.y;
	}
};

inline
Vector2 operator + (Vector2 v1, Vector2 v2)
{
	return Vector2(v1.x + v2.x, v1.y + v2.y);
}

inline
Vector2 operator - (Vector2 v1, Vector2 v2)
{
	return Vector2(v1.x - v2.x, v1.y - v2.y);
}

inline 
Vector2 operator * (Vector2 v1,  Vector2 c)
{
	return Vector2(v1.x * c.x, v1.y * c.y);
}

template<typename T> inline
Vector2 operator * (Vector2 v1, const T t)
{
	return Vector2(v1.x * t, v1.y * t);
}

template <typename T> inline
Vector2 operator / (Vector2 v1, T t)
{
	return Vector2(v1.x / t, v1.y / t);
}

inline
Vector2 Normalize(Vector2 v)
{
	double normal = sqrt(v.x * v.x + v.y * v.y);
	return Vector2((float)(v.x / normal),(float)( v.y / normal));
}
inline
Vector2 Normalize(Vector2 v1, Vector2 v2)
{
	Vector2 vec = v1 - v2;
	double normal = sqrt(vec.x * vec.x + vec.y * vec.y);
	Vector2 vel = Vector2((float)(vec.x / normal), (float)(vec.y / normal));

	return vel;
}

inline
float dot(Vector2 v1, Vector2 v2)
{
	return (v1.x * v2.x + v1.y * v2.y);
}

inline
float cross(Vector2 v1, Vector2 v2)
{
	return (v1.x * v2.y - v1.y * v2.x);
}

typedef Vector2 Position;