#include "Number.h"
#include <RRMLib.h>

static const float NUMBER_W = 84.4f;
static const float NUMBER_H = 88.5f;

static const int NUM = 10;
static const Vector2 UV[NUM]
{
	Vector2(NUMBER_W * 0, NUMBER_H * 0),
	Vector2(NUMBER_W * 1, NUMBER_H * 0),
	Vector2(NUMBER_W * 2, NUMBER_H * 0),
	Vector2(NUMBER_W * 3, NUMBER_H * 0),
	Vector2(NUMBER_W * 4, NUMBER_H * 0),
	Vector2(NUMBER_W * 0, NUMBER_H * 1),
	Vector2(NUMBER_W * 1, NUMBER_H * 1),
	Vector2(NUMBER_W * 2, NUMBER_H * 1),
	Vector2(NUMBER_W * 3, NUMBER_H * 1),
	Vector2(NUMBER_W * 4, NUMBER_H * 1),
};

Number::Number(const Position& pos, float size)
{
	_handle = RRMLib::LoadGraph("Resource/img/UI/Number/Number.png");
	_pos = pos;
	_size = size;
	_offset = size / 2;
}


Number::~Number()
{
}

void
Number::Draw(long long num)
{
	int i = 0;
	Vector2 uv;

	int number = num;
	while (number > 9)
	{
		int idx = number % 10;
		uv = UV[idx];
		RRMLib::DrawRectExtendGraph((_pos.x - _size / 2) - i * _offset, (_pos.y - _size / 2),
			(_pos.x + _size / 2) - i * _offset, _pos.y + _size / 2,
			uv.x, uv.y, NUMBER_W, NUMBER_H, _handle, true, false);

		++i;
		number /= 10;
	}
	uv = UV[number % 10];

	//‰ºˆêŒ…
	RRMLib::DrawRectExtendGraph((_pos.x - _size / 2) - i * _offset, (_pos.y - _size / 2),
		(_pos.x + _size / 2) - i * _offset, _pos.y + _size / 2,
		uv.x, uv.y, NUMBER_W, NUMBER_H, _handle, true, false);
}
