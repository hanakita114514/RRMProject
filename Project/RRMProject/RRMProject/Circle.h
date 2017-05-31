#pragma once

#include "Vector2.h"

struct Circle
{
	Position pos;
	float radius;
	Position center;

	Circle() : pos(0, 0), radius(0)
	{

	}
	Circle(const Position& fpos, const float& r) : pos(fpos), radius(r)
	{

	}
	Circle(const float& x, const float& y, const float& r) : pos(x, y), radius(r)
	{

	}

	void DrawCircle();
	void DrawGraph(int handle);
};