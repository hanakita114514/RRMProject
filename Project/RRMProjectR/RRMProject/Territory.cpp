#include "Territory.h"


Territory::Territory()
{
}


Territory::~Territory()
{
}

void
Territory::Set(float xRange, float yRange, Vector2 pos)
{
	Rect r = {};
	r.w = xRange;
	r.h = yRange;
	r.pos = pos - Vector2(r.w / 2,0);

	_range = r;
	_outRange = false;
}
void
Territory::Update(const Rect& rc)
{
	Rect r = rc;
	if (r.Left() < _range.Left() || r.Right() > _range.Right())
	{
		_outRange = true;
	}
}
