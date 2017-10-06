#include "Vector3.h"
#include <cmath>
#include <DxLib.h>

namespace DxLib
{
	VECTOR GetVector3ToVECTOR(const Vector3& v)
	{
		return VGet(v.x, v.y, v.z);
	}
}

//-----------------------------------------------
//コンストラクタ
//-----------------------------------------------
Vector3::Vector3()
{
	x = 0.0f; y = 0.0f; z = 0.0f;
}

Vector3::Vector3(const float fx, const float fy, const float fz)
{
	x = fx; y = fy; z = fz;
}

Vector3::Vector3(const Vector3& v)
{
	x = v.x; y = v.y; z = v.z;
}

//-----------------------------------------------
//演算子のオーバーロード
//-----------------------------------------------
void Vector3::operator = (const float fv)
{
	x = fv; y = fv; z = fv;
}

void Vector3::operator += (const float fv)
{
	x += fv; y += fv; z += fv;
}

void Vector3::operator -= (const float fv)
{
	x -= fv; y -= fv; z -= fv;
}

void Vector3::operator *= (const float fv)
{
	x *= fv; y *= fv; z *= fv;
}

void  Vector3::operator /= (const float fv)
{
	if (fv != 0.0f)
	{
		x /= fv; y /= fv; z /= fv;
	}
}

void Vector3::operator += (const Vector3& v)
{
	x += v.x; y += v.y; z += v.z;
}

void Vector3::operator -= (const Vector3& v)
{
	x -= v.x; y -= v.y; z -= v.z;
}

void Vector3::operator *= (const Vector3& v)
{
	x *= v.x; y *= v.y; z *= v.z;
}

void Vector3::operator /= (const Vector3& v)
{
	if (v.x != 0.0f)
	{
		x /= v.x;
	}
	if (v.y != 0.0f)
	{
		y /= v.y;
	}
	if (v.z != 0)
	{
		z /= v.z;
	}
}


//-----------------------------------------------
//Vector3内のその他関数
//-----------------------------------------------

float MySqrt(float f)
{
	float r=1.0f;
	//漸化式使用
	for (int i = 0; i <= 20; ++i)
	{
		r = 1 + (f - 1) / (r + 1);
	}
	return r;
}
float Vector3::Length()
{
	//float r1 = MySqrt(x*x + y*y + z*z);
	//float r2 = sqrtf(x*x + y*y + z*z);
	//return MySqrt(x*x + y*y + z*z);
	return sqrtf(x*x + y*y + z*z);
}

float Vector3::NotSqrtLength()
{
	return x * x + y * y + z * z;
}

Vector3 Vector3::Normalized()
{
	float l = Length();
	return Vector3(x / l, y / l,z / l);
}

float Vector3::Dot(const Vector3& v)
{
	
	return x * v.x + y * v.y + z * v.z;
}

Vector3 Vector3::Cross(const Vector3& v)
{
	return Vector3(y*v.z - z*v.y, z*v.x - x*v.z, x*v.y - y*v.x);
}

bool Vector3::IsVertival(const Vector3& r)
{
	float d = Dot(r);
	return (-0.000001f < d && d < 0.000001f);
}

bool Vector3::IsParallel(const Vector3& r)
{
	float d = Cross(r).NotSqrtLength();
	return (-0.000001f < d && d < 0.000001f);
}

bool Vector3::IsSharpAngle(const Vector3& r)
{
	return (Dot(r) >= 0.0f);
}

void Vector3::Draw(const float posX, const float posY, unsigned int col)
{
	DrawFormatString(posX, posY, col, "x = %f,y = %f,z = %f", x, y, z);
}

VECTOR Vector3::GetVECTOR()
{
	return VGet(x, y, z);
}

//-----------------------------------------------
//その他関数
//-----------------------------------------------

