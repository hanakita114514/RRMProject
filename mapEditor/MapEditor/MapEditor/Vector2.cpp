#include "Vector2.h"
#include <cmath>
#include <DxLib.h>

//-----------------------------------------------
//コンストラクタ
//-----------------------------------------------
Vector2::Vector2()
{
	x = 0.0f; y = 0.0f;
}

Vector2::Vector2(const float fx, const float fy)
{
	x = fx; y = fy;
}

Vector2::Vector2(const Vector2& v)
{
	x = v.x; y = v.y;
}

//-----------------------------------------------
//演算子のオーバーロード
//-----------------------------------------------
void Vector2::operator = (const float fv)
{
	x = fv; y = fv;
}

void Vector2::operator += (const float fv)
{
	x += fv; y += fv;
}

void Vector2::operator -= (const float fv)
{
	x -= fv; y -= fv;
}

void Vector2::operator *= (const float fv)
{
	x *= fv; y *= fv;
}

void  Vector2::operator /= (const float fv)
{
	if (fv != 0.0f)
	{
		x /= fv; y /= fv;
	}
}

void Vector2::operator += (const Vector2& v)
{
	x += v.x; y += v.y;
}

void Vector2::operator -= (const Vector2& v)
{
	x -= v.x; y -= v.y;
}

void Vector2::operator *= (const Vector2& v)
{
	x *= v.x; y *= v.y;
}

void Vector2::operator /= (const Vector2& v)
{
	if (v.x != 0.0f)
	{
		x /= v.x;
	}
	if (v.y != 0.0f)
	{
		y /= v.y;
	}
}


//-----------------------------------------------
//Vector2内のその他関数
//-----------------------------------------------

float Vector2::Length()
{
	return hypotf(x,y);
}

Vector2 Vector2::Normalized()
{
	float l = Length();
	return Vector2(x / l, y / l);
}

float Vector2::Dot(const Vector2& v)
{

	return x * v.x + y * v.y;
}

float Vector2::Cross(const Vector2& v)
{
	return x*v.y - v.x*y;
}

void Vector2::Draw(const float posX, const float posY, unsigned int col)
{
	DrawFormatString(posX, posY, col, "x = %f,y = %f", x, y);
}

//-----------------------------------------------
//その他関数
//-----------------------------------------------

float Length(const Vector2& v)
{
	return hypotf(v.x, v.y);
}

Vector2 Normalized(const Vector2& v)
{
	float l = Length(v);
	return Vector2(v.x / l, v.y / l);
}

float Dot(const Vector2& v1, const Vector2& v2)
{
	return v1.x*v2.x + v1.y*v2.y;
}

float Cross(const Vector2& v1, const Vector2& v2)
{
	return v1.x*v2.y - v2.x*v1.y;
}