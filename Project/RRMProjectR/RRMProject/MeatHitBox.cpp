#include "MeatHitBox.h"
#include "RRMLib.h"

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

void
MeatHitBox::Attack(float frame, const Rect& rc, const Vector2& dir)
{
	Rect r = {};
	Rect work = rc;
	HitBox hitBox;

	if (dir.x > 0)
	{
		r.w = 20;
		r.h = 32;
		r.pos = Vector2(work.Right(), work.pos.y);
	}
	else
	{
		r.w = 20;
		r.h = 32;
		r.pos = work.pos;
	}

	hitBox.power = 100;
	hitBox.hitstop = 1.0f;
	hitBox.rc = r;
	hitBox.vec = Vector2(dir.x * 10, -10.0f);

	RRMLib::DrawBox(r.pos.x, r.pos.y, r.Bottom(), r.Right(), 0xffffff, true);

	_attackBox.clear();
	_attackBox.push_back(hitBox);

}
