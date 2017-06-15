#include "Circle.h"
#include <DxLib.h>

void
Circle::DrawCircle()
{
	DxLib::DrawCircle((int)pos.x, (int)pos.y, (int)radius, 0xffffffff, false);
}

void
Circle::DrawGraph(int handle)
{
	DxLib::DrawGraph((int)(pos.x - radius), (int)(pos.y - radius), handle, true);
}