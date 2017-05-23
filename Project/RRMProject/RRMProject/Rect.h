#pragma once

#include "Vector2.h"

struct Rect
{
	Position pos;
	float h;
	float w;

	Rect() : pos(0, 0), h(0), w(0)
	{

	}
	Rect(const Position& fpos, const float& height, const float& width) :
		pos(fpos), h(height), w(width)
	{

	}
	Rect(const float& x, const float& y, const float& height, const float& width) :
		pos(x, y), h(height), w(width)
	{

	}

	void SetTop(float fy)
	{
		pos.y = fy;
	}

	void SetBottom(float fy)
	{
		pos.y = fy - h;
	}
	void SetLeft(float fx)
	{
		pos.x = fx;
	}

	void SetRight(float fx)
	{
		pos.x = fx - w;
	}

	float Bottom() { return pos.y + h; }
	float Top() { return pos.y; }
	float Right() { return pos.x + w; }
	float Left() { return pos.x; }
	Position Center() { return Position(pos.x + w / 2, pos.y + h / 2); }

	void DrawBox();
};