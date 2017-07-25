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

	static const float HEIGHT = 50.f;
	static const float WIDTH = 100.f;

	const HitBox hitBox[] = 
	{
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x), rc.pos.y + rc.h / 2), HEIGHT , WIDTH), Vector2(0,0), Vector2(dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x), rc.pos.y + rc.h / 2 - 1 * 4), HEIGHT , WIDTH), Vector2(0,0), Vector2(dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x), rc.pos.y + rc.h / 2 - 2 * 4), HEIGHT , WIDTH), Vector2(0,0), Vector2(dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x), rc.pos.y + rc.h / 2 - 3 * 4), HEIGHT , WIDTH), Vector2(0,0), Vector2(dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x), rc.pos.y + rc.h / 2 - 4 * 4), HEIGHT , WIDTH), Vector2(0,0), Vector2(dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x), rc.pos.y + rc.h / 2 - 5 * 4), HEIGHT , WIDTH), Vector2(0,0), Vector2(dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x), rc.pos.y + rc.h / 2 - 6 * 4), HEIGHT , WIDTH), Vector2(0,0), Vector2(dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x), rc.pos.y + rc.h / 2 - 7 * 4), HEIGHT , WIDTH), Vector2(0,0), Vector2(dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x), rc.pos.y + rc.h / 2 - 8 * 4), HEIGHT , WIDTH), Vector2(0,0), Vector2(dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x), rc.pos.y + rc.h / 2 - 9 * 4), HEIGHT , WIDTH), Vector2(0,0), Vector2(dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x), rc.pos.y + rc.h / 2 - 10 * 4), HEIGHT , WIDTH), Vector2(0,0), Vector2(dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x), rc.pos.y + rc.h / 2 - 11* 4), HEIGHT , WIDTH), Vector2(0,0), Vector2(dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x), rc.pos.y + rc.h / 2 - 12 * 4), HEIGHT , WIDTH), Vector2(0,0), Vector2(dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x), rc.pos.y + rc.h / 2 - 13 * 4), HEIGHT , WIDTH), Vector2(0,0), Vector2(dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x), rc.pos.y + rc.h / 2 - 14 * 4), HEIGHT , WIDTH), Vector2(0,0), Vector2(dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x), rc.pos.y + rc.h / 2 - 15 * 4), HEIGHT , WIDTH), Vector2(0,0), Vector2(dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x), rc.pos.y + rc.h / 2 - 16 * 4), HEIGHT , WIDTH), Vector2(0,0), Vector2(dir.x, 0)),
	};

	_attackboxes.clear();
	_attackboxes.push_back(hitBox[(int)frame]);
}

void 
PlayerHitBox::SecondAttack(float frame, const Rect& rc, const Vector2& dir)
{

	static const float HEIGHT = 50.f;
	static const float WIDTH = 100.f;

	const HitBox hitBox[] =
	{
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x), rc.pos.y + rc.h / 2), HEIGHT , WIDTH), Vector2( 5 * -dir.x, 0), Vector2(-dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((10 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * -dir.x, -5), Vector2(-dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((10 + 10) * dir.x)), rc.pos.y + rc.h / 2 ), HEIGHT , WIDTH),Vector2(8 * -dir.x, -5), Vector2(-dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((10 + 15) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH), Vector2(8 * -dir.x, -5), Vector2(-dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((10 + 20) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH), Vector2(8 * -dir.x, -5), Vector2(-dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((10 + 25) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH), Vector2(8 * -dir.x, -5), Vector2(-dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((10 + 30) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH), Vector2(8 * -dir.x, -5), Vector2(-dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((10 + 35) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH), Vector2(8 * -dir.x, -5), Vector2(-dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((10 + 40) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH), Vector2(8 * -dir.x, -5), Vector2(-dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((10 + 45) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH), Vector2(8 * -dir.x, -5), Vector2(-dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((10 + 50) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH), Vector2(8 * -dir.x, -5), Vector2(-dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((10 + 55) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH), Vector2(8 * -dir.x, -5), Vector2(-dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((10 + 60) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH), Vector2(8 * -dir.x, -5), Vector2(-dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((10 + 65) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH), Vector2(8 * -dir.x, -5), Vector2(-dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((10 + 70) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH), Vector2(8 * -dir.x, -5), Vector2(-dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((10 + 75) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH), Vector2(8 * -dir.x, -5), Vector2(-dir.x, 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((10 + 80) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH), Vector2(8 * -dir.x, -5), Vector2(-dir.x, 0)),
	};

	_attackboxes.clear();
	_attackboxes.push_back(hitBox[(int)frame]);
}

void 
PlayerHitBox::ThirdAttack(float frame, const Rect&rc, const Vector2& dir)
{
	static const float HEIGHT = 50.f;
	static const float WIDTH = 100.f;
	const HitBox hitBox[] =
	{
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((390 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -20), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((380 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -20), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((370 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -20), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((360 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -20), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((350 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -20), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((340 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -20), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((330 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -20), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((320 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -20), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((310 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -20), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((300 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -20), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((290 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -20), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((280 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -20), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((270 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -20), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((260 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -20), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((250 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -20), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((240 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -20), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((230 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -20), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((220 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -20), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((210 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -20), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((200 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -20), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((190 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -20), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((180 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -20), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((170 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -20), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((160 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -20), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((150 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -20), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((140 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -20), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((130 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -20), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((120 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -5), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((110 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -5), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((100 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -5), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((90 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -5), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((80 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -5), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((70 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -5), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((60 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -5), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((50 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -5), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((40 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -5), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((30 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -5), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((20 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -5), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x + ((10 + 5) * dir.x)), rc.pos.y + rc.h / 2), HEIGHT , WIDTH),  Vector2(8 * dir.x, -5), Vector2(dir.x , 0)),
		HitBox(20, 4, Rect(Position(rc.pos.x + ((dir.x == -1 ? WIDTH : rc.w) * dir.x), rc.pos.y + rc.h / 2), HEIGHT , WIDTH), Vector2(10 * dir.x, 0), Vector2(dir.x , 0)),
	};

	_attackboxes.clear();
	_attackboxes.push_back(hitBox[(int)frame]);
}

void 
PlayerHitBox::UpAttack(float frame, const Rect& rc, const Vector2& dir)
{
	static const float WIDTH = 100.f;
	static const float HEIGHT = 50.f;
	HitBox hb = HitBox(20, 4, Rect(Position(rc.pos.x, rc.pos.y - HEIGHT), HEIGHT, WIDTH), Vector2(2 * dir.x, -12), Vector2(dir.x, 0));

	_attackboxes.clear();
	_attackboxes.push_back(hb);
}

PlayerHitBox::DamageBox(float frame, const Rect& rc, const Vector2& dir)
{
	HitBox hb = HitBox(0, 0, Rect(Position(rc.pos.x + 8, rc.pos.y + 8),48,48));

	_damageBox.clear();
	_damageBox.push_back(hb);
}


void
PlayerHitBox::Draw(){
	for (auto& a : _attackboxes)
	{
		a.rc.DrawGraph(handle, a.dir);
	}
	for (auto& d : _damageBox)
	{
		d.rc.DrawBox();	}
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