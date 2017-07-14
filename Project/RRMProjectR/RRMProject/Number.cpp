#include "Number.h"
#include <RRMLib.h>


Number::Number(float size) :
	NUMBER_W(84.4f), NUMBER_H(88.5f)
{
	_handle = RRMLib::LoadGraph("Resource/img/UI/Number/Number.png");
	_size = size;
	_offset = size / 2;

	std::array<Vector2, NUM> UV
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

	_uv = UV;
}

Number::Number(float size, int handle, float width, float height)
	: NUMBER_W(width), NUMBER_H(height)
{
	_size = size;
	_offset = size / 2;
	_handle = handle;

	std::array<Vector2, NUM> UV
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

	_uv = UV;
}


Number::~Number()
{
}

Vector2 
Number::UV(int idx)
{
	return _uv[idx];
}

void
Number::Draw(long long num, const Position& pos)
{
	int i = 0;
	Vector2 uv;

	int number = num;
	while (number > 9)
	{
		int idx = number % 10;
		uv = UV(idx);
		RRMLib::DrawRectExtendGraph((pos.x - _size / 2) - i * _offset, (pos.y - _size / 2),
			(pos.x + _size / 2) - i * _offset, pos.y + _size / 2,
			uv.x, uv.y, NUMBER_W, NUMBER_H, _handle, true, false);

		++i;
		number /= 10;
	}

	uv = UV(number % 10);

	//‰ºˆêŒ…
	RRMLib::DrawRectExtendGraph((pos.x - _size / 2) - i * _offset, (pos.y - _size / 2),
		(pos.x + _size / 2) - i * _offset, pos.y + _size / 2,
		uv.x, uv.y, NUMBER_W, NUMBER_H, _handle, true, false);
}

void 
Number::Draw(long long num, const Position& pos ,Vector2 extendSize)
{
	int i = 0;
	Vector2 uv;

	int number = num;
	while (number > 9)
	{
		int idx = number % 10;
		uv = UV(idx);
		RRMLib::DrawRectExtendGraph((pos.x - _size / 2 - extendSize.x / 2) - i * _offset, (pos.y - _size / 2 - extendSize.y / 2),
			(pos.x + _size / 2 + extendSize.x / 2) - i * _offset, pos.y + _size / 2 + extendSize.x / 2,
			uv.x, uv.y, NUMBER_W, NUMBER_H, _handle, true, false);

		++i;
		number /= 10;
	}

	uv = UV(number % 10);

	//‰ºˆêŒ…
	RRMLib::DrawRectExtendGraph((pos.x - _size / 2 - extendSize.x / 2) - i * _offset, (pos.y - _size / 2 - extendSize.y / 2),
		(pos.x + _size / 2 + extendSize.x / 2) - i * _offset, pos.y + _size / 2 + extendSize.x / 2,
		uv.x, uv.y, NUMBER_W, NUMBER_H, _handle, true, false);
}