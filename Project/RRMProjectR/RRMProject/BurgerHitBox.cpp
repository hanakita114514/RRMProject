#include "BurgerHitBox.h"



BurgerHitBox::BurgerHitBox()
{
}


BurgerHitBox::~BurgerHitBox()
{
}

void 
BurgerHitBox::Search(float frame, const Rect& rc, const Vector2& dir)
{

}

void
BurgerHitBox::Foot(float frame, const Rect& rc, const Vector2& dir)
{

}
void 
BurgerHitBox::Attack(float frame, const Rect& rc, const Vector2& dir)
{
	HitBox hitBox;
	Rect rect;

	//‰EŒü‚«
	if (dir.x > 0)
	{
		rect.w = 196;
		rect.h = 196;
		rect.pos = rc.pos;
	}
	else
	{
		rect.w = 196;
		rect.h = 196;
		rect.pos = rc.pos;
	}

	hitBox.hitstop = 3.0f;
	hitBox.power = 150.f;
	hitBox.rc = rect;
	hitBox.vec = Vector2(dir.x * 10, -15.0f);

	_attackBox.clear();
	_attackBox.push_back(hitBox);
}