#include "Circle.h"
#include <DxLib.h>

void
Circle::DrawCircle()
{
	DxLib::DrawCircle(pos.x, pos.y, radius, 0xffffffff, false);
}

void
Circle::DrawGraph(int handle)
{
	DxLib::DrawGraph(pos.x - radius, pos.y - radius, handle, true);
}