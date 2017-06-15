#include "Rect.h"
#include <DxLib.h>

void
Rect::DrawBox()
{
	DxLib::DrawBox(pos.x, pos.y, pos.x + w, pos.y + h, GetColor(255,0,0), false);
}

void 
Rect::DrawGraph(int handle)
{
	DxLib::DrawGraph((int)pos.x, (int)pos.y, handle, true);
}