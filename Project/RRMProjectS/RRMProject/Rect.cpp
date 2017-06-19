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
	RRMLib::DrawGraph((int)pos.x, (int)pos.y, handle);
}