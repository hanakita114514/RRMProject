#include "Circle.h"
#include <RRMLib.h>

void
Circle::DrawCircle()
{
	RRMLib::DrawCircle((int)pos.x, (int)pos.y, (int)radius, 0xffffffff, false);
}

void
Circle::DrawGraph(int handle)
{
	RRMLib::DrawGraph((int)(pos.x - radius), (int)(pos.y - radius), handle, true);
}