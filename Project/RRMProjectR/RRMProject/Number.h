#pragma once

#include "Vector2.h"
#include <array>

class Number
{
private:
	float _size;

	int _handle;
	float _offset;

	static const int NUM = 10;

	std::array<Vector2, NUM> _uv;
	Vector2 UV(int idx);

	const float NUMBER_W;
	const float NUMBER_H;

public:
	Number(float size);
	Number(float size, int handle, float width, float height);
	~Number();

	void Draw(long long num, const Position& pos);
	void Draw(long long num, const Position& pos ,Vector2 extendSize);
};

