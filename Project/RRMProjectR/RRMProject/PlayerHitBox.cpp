#include "PlayerHitBox.h"
#include <RRMLib.h>


PlayerHitBox::PlayerHitBox()
{
}


PlayerHitBox::~PlayerHitBox()
{
}

void 
PlayerHitBox::FirstAttack(float frame, const Rect& rc, const Vector2& dir)
{
	const HitBox hitBox[] = 
	{
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x), rc.pos.y), 50 , 50)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x), rc.pos.y - 1 * 4), 50 , 50)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x), rc.pos.y - 2 * 4), 50 , 50)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x), rc.pos.y - 3 * 4), 50 , 50)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x), rc.pos.y - 4 * 4), 50 , 50)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x), rc.pos.y - 5 * 4), 50 , 50)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x), rc.pos.y - 6 * 4), 50 , 50)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x), rc.pos.y - 7 * 4), 50 , 50)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x), rc.pos.y - 8 * 4), 50 , 50)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x), rc.pos.y - 9 * 4), 50 , 50)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x), rc.pos.y - 10 * 4), 50 , 50)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x), rc.pos.y - 11* 4), 50 , 50)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x), rc.pos.y - 12 * 4), 50 , 50)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x), rc.pos.y - 13 * 4), 50 , 50)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x), rc.pos.y - 14 * 4), 50 , 50)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x), rc.pos.y - 15 * 4), 50 , 50)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x), rc.pos.y - 16 * 4), 50 , 50)),
	};

	_attackboxes.clear();
	_attackboxes.push_back(hitBox[(int)frame]);
}

void 
PlayerHitBox::SecondAttack(float frame, const Rect& rc, const Vector2& dir)
{
	const HitBox hitBox[] =
	{
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x), rc.pos.y), 50 , 50), Vector2( 5 * dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((10 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -5)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((10 + 10) * dir.x)), rc.pos.y ), 50 , 50),Vector2(8 * dir.x, -5)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((10 + 15) * dir.x)), rc.pos.y), 50 , 50), Vector2(8 * dir.x, -5)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((10 + 20) * dir.x)), rc.pos.y), 50 , 50), Vector2(8 * dir.x, -5)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((10 + 25) * dir.x)), rc.pos.y), 50 , 50), Vector2(8 * dir.x, -5)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((10 + 30) * dir.x)), rc.pos.y), 50 , 50), Vector2(8 * dir.x, -5)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((10 + 35) * dir.x)), rc.pos.y), 50 , 50), Vector2(8 * dir.x, -5)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((10 + 40) * dir.x)), rc.pos.y), 50 , 50), Vector2(8 * dir.x, -5)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((10 + 45) * dir.x)), rc.pos.y), 50 , 50), Vector2(8 * dir.x, -5)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((10 + 50) * dir.x)), rc.pos.y), 50 , 50), Vector2(8 * dir.x, -5)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((10 + 55) * dir.x)), rc.pos.y), 50 , 50), Vector2(8 * dir.x, -5)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((10 + 60) * dir.x)), rc.pos.y), 50 , 50), Vector2(8 * dir.x, -5)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((10 + 65) * dir.x)), rc.pos.y), 50 , 50), Vector2(8 * dir.x, -5)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((10 + 70) * dir.x)), rc.pos.y), 50 , 50), Vector2(8 * dir.x, -5)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((10 + 75) * dir.x)), rc.pos.y), 50 , 50), Vector2(8 * dir.x, -5)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((10 + 80) * dir.x)), rc.pos.y), 50 , 50), Vector2(8 * dir.x, -5)),
	};

	_attackboxes.clear();
	_attackboxes.push_back(hitBox[(int)frame]);
}

void 
PlayerHitBox::ThirdAttack(float frame, const Rect&rc, const Vector2& dir)
{
	const HitBox hitBox[] =
	{
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((390 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -20)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((380 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -20)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((370 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -20)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((360 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -20)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((350 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -20)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((340 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -20)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((330 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -20)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((320 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -20)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((310 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -20)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((300 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -20)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((290 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -20)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((280 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -20)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((270 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -20)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((260 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -20)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((250 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -20)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((240 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -20)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((230 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -20)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((220 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -20)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((210 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -20)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((200 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -20)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((190 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -20)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((180 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -20)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((170 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -20)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((160 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -20)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((150 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -20)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((140 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -20)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((130 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -20)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((120 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -5)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((110 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -5)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((100 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -5)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((90 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -5)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((80 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -5)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((70 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -5)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((60 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -5)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((50 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -5)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((40 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -5)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((30 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -5)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((20 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -5)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x + ((10 + 5) * dir.x)), rc.pos.y), 50 , 50),  Vector2(8 * dir.x, -5)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? 50 : rc.w) * dir.x), rc.pos.y), 50 , 50), Vector2(5 * dir.x, 0)),
	};

	_attackboxes.clear();
	_attackboxes.push_back(hitBox[(int)frame]);
}

void 
PlayerHitBox::UpAttack(float frame, const Rect& rc, const Vector2& dir)
{
	HitBox hb = HitBox(20, 4, Rect(Position(rc.pos.x, rc.pos.y - rc.h), 50, 50), Vector2(2 * dir.x, -5));

	_attackboxes.clear();
	_attackboxes.push_back(hb);
}

void
PlayerHitBox::Draw()
{
	for (auto& a : _attackboxes)
	{
		RRMLib::DrawBox(a.rc.Left(), a.rc.Top(), a.rc.Right(), a.rc.Bottom(), 0xffffffff, false);
	}
	for (auto& d : _damageBox)
	{
		RRMLib::DrawBox(d.rc.Left(), d.rc.Top(), d.rc.Right(), d.rc.Bottom(), 0xffffffff, false);

	}
}

void
PlayerHitBox::Clear()
{
	_attackboxes.clear();
	_damageBox.clear();
}

std::vector<HitBox>&
PlayerHitBox::GetAttackBoxes()
{
	return _attackboxes;
}

std::vector<HitBox>& 
PlayerHitBox::GetDamageBoxes()
{
	return _damageBox;
}