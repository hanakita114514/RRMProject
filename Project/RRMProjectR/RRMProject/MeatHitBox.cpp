#include "MeatHitBox.h"

MeatHitBox::MeatHitBox()
{
}


MeatHitBox::~MeatHitBox()
{
}

void
MeatHitBox::Search(float frame, const Rect& rc, const Vector2& dir)
{
	Rect r = {};

	if (dir.x > 0)
	{
		r.w = 100;
		r.h = 32;
		r.pos = Position(rc.pos.x + r.w, rc.pos.y);
	}
	else
	{
		r.w = 100;
		r.h = 32;
		r.pos = Position(rc.pos.x - r.w, rc.pos.y);
	}

	_searchRect.clear();
	_searchRect.push_back(r);
}
