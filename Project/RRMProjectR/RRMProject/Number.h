#pragma once

#include "Vector2.h"

class Number
{
private:
	Position _pos;
	float _size;

	int _handle;
	float _offset;

public:
	Number(const Position& pos, float size);
	~Number();

	void Draw(long long num);
};

