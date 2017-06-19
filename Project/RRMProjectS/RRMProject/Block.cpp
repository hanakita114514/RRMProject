#include "Block.h"
#include <RRMLib.h>


Block::Block()
{
}


Block::~Block()
{
}

void Block::Initialize(Vector2 pos, int handle,Vector2 size)
{
	Rect r = {};
	_rc = r;

	_rc.pos = pos;
	_rc.h = size.y;
	_rc.w = size.x;

	_handle = handle;
	_objType = ObjectType::common;
}

void Block::Draw(const Vector2& offset)
{
	Vector2 drawPos;
	drawPos.x = _rc.pos.x - offset.x;
	drawPos.y = _rc.pos.y - offset.y;

	RRMLib::DrawGraph((int)drawPos.x, (int)drawPos.y, _handle);
}
