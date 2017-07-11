#pragma once

#include "Vector2.h"

class Number
{
private:
	Position _pos;
	float _size;

	int _handle;
	float _offset;

	float _width;
	float _height;

public:
	Number(const Position& pos, float size);
	Number(const Position& pos, float size, int handle, float width, float height);
	~Number();

	void Draw(long long num);
};

