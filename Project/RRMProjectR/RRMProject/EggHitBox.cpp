#include "EggHitBox.h"

EggHitBox::EggHitBox()
{
}


EggHitBox::~EggHitBox()
{
}

void 
EggHitBox::Search(float frame, const Rect& rc, const Vector2& dir)
{
	Rect rect = {};

	if (dir.x > 0)		//‰EŒü‚«
	{
		rect.w = 200;
		rect.h = 64;
		rect.pos = Position(rc.pos.x + rect.w, rc.pos.y + 10);
	}
	else
	{
		rect.w = 200;
		rect.h = 64;
		rect.pos = Position(rc.pos.x - rect.w, rc.pos.y + 10);
	}

	_searchRect.clear();
	_searchRect.push_back(rect);
}

void
EggHitBox::Foot(float frame, const Rect& rc, const Vector2& dir)
{
	Rect rect = {};

	if (dir.x > 0)		//‰EŒü‚«
	{
		rect.w = 2;
		rect.h = 5;
		rect.pos = Position(rc.pos.x + rc.w, rc.pos.y + 10);
	}
	else
	{
		rect.w = 2;
		rect.h = 5;
		rect.pos = Position(rc.pos.x - rc.w, rc.pos.y + 10);
	}

	_footRect.clear();
	_footRect.push_back(rect);

}
