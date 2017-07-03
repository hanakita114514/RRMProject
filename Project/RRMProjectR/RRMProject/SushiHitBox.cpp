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
		rect.h = 2;
	}
	else
	{
		rect.pos = Position(rc.pos.x, rc.pos.y + rc.h);
		rect.w = 2;
		rect.h = 2;
	}
	_searchRect.clear();
	_searchRect.push_back(rect);
}

void 
SushiHitBox::Attack(float frame, const Rect& rc, const Vector2& dir)
{

}