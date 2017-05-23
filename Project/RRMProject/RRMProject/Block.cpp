#include "Block.h"
#include <DxLib.h>


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

void Block::Draw()
{
	DxLib::DrawGraph(_rc.pos.x, _rc.pos.y, _handle, true);
	DxLib::DrawBox(_rc.Left(), _rc.Top(), _rc.Right() + 1, _rc.Bottom() + 1, 0xff0000, false);
}
