#include "ThroughBlock.h"
#include <RRMLib.h>


ThroughBlock::ThroughBlock()
{
}


ThroughBlock::~ThroughBlock()
{
}

void
ThroughBlock::Initialize(Vector2 pos, int handle, Vector2 size, BlockType type)
{
	Rect r = {};
	r.pos = pos;
	r.h = size.y;
	r.w = size.x;
	_rc = r;

	_blockType = type;
	_objType = ObjectType::common;
	_handle = handle;
}

void
ThroughBlock::Draw(const Vector2& offset)
{
	Vector2 drawPos;
	drawPos.x = _rc.pos.x - offset.x;
	drawPos.y = _rc.pos.y - offset.y;

	RRMLib::DrawGraph((int)drawPos.x, (int)drawPos.y, _handle);

}


