#include "Rect.h"
#include <DxLib.h>

void
Rect::DrawBox()
{
	DxLib::DrawBox(pos.x, pos.y, pos.x + w, pos.y + h, 0xffffffff, false);
}