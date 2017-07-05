#include "SushiHitBox.h"



SushiHitBox::SushiHitBox()
{
}


SushiHitBox::~SushiHitBox()
{
}

void 
SushiHitBox::Search(float frame, const Rect& rc, const Vector2& dir)
{
	Rect rect;

	//‰EŒü‚«
	if (dir.x > 0)
	{
		rect.w = 150;
		rect.h = 15;
		rect.pos = Position(rc.pos.x + rc.w, rc.pos.y + 10);
	}
	else
	{
		rect.w = 150;
		rect.h = 15;
		rect.pos = Position(rc.pos.x - rect.w, rc.pos.y + 10);
	}

	_searchRect.clear();
	_searchRect.push_back(rect);
}
void 
SushiHitBox::Foot(float frame, const Rect& rc, const Vector2& dir)
{
	Rect rect;
	//‰EŒü‚«
	if (dir.x > 0)
	{
		rect.pos = Position(rc.pos.x + rc.w, rc.pos.y + rc.h);
		rect.w = 2;
		rect.h = 5;
	}
	else
	{
		rect.pos = Position(rc.pos.x, rc.pos.y + rc.h);
		rect.w = 2;
		rect.h = 5;
	}

	_footRect.clear();
	_footRect.push_back(rect);
}

void 
SushiHitBox::Attack(float frame, const Rect& rc, const Vector2& dir)
{
	HitBox hitBox;
	Rect rect;

	//‰EŒü‚«
	if (dir.x > 0)
	{
		rect.w = 50;
		rect.h = 30;
		//rect.pos = Position(rc.pos.x + rc.w, rc.pos.y);
		rect.pos = rc.pos;
	}
	else
	{
		rect.w = 50;
		rect.h = 30;
		//rect.pos = Position(rc.pos.x - rect.w, rc.pos.y);
		rect.pos = rc.pos;
	}

	hitBox.hitstop = 3.0f;
	hitBox.power = 10.0f;
	hitBox.rc = rect;
	hitBox.vec = Vector2(dir.x * 10, -15.0f);

	_attackBox.clear();
	_attackBox.push_back(hitBox);
}