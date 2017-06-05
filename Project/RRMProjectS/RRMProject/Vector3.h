#pragma once

struct Vector3
{
	float x, y, z;

	Vector3() : x(0), y(0),z(0)
	{

	}

	Vector3(float fx, float fy, float fz) : x(fx), y(fy), z(fz)
	{

	}

	void operator += (const Vector3 v)
	{
		x += v.x;
		y += v.y;
		z += v.z;
	}

	void operator -= (const Vector3 v)
	{
		x -= v.x;
		y -= v.y;
		z -= v.z;
	}
};

inline
Vector3 operator + (Vector3 v1, Vector3 v2)
{
	return Vector3(v1.x + v2.z, v1.y + v2.y, v1.z + v2.z);
}

inline
Vector3 operator - (Vector3 v1, Vector3 v2)
{
	return Vector3(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
}

