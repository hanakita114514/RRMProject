#include "Rect.h"
#include <RRMLib.h>

void
Rect::DrawBox()
{
	RRMLib::DrawBox(pos.x, pos.y, pos.x + w, pos.y + h, RRMLib::GetColor(255,0,0), false);
}

void 
Rect::DrawGraph(int handle)
{
	RRMLib::DrawGraph(pos.x, pos.y, handle, true);
}

void 
Rect::DrawGraph(int handle, const Vector2& dir)
{
	RRMLib::DrawExtendGraph(pos.x, pos.y, pos.x + w, pos.y + h, handle, true, dir.x < 0);
}