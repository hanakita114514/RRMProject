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

	_hitboxes.clear();
	_hitboxes.push_back(hitBox[(int)frame]);
}

void
PlayerHitBox::Draw()
{
	for (auto h : _hitboxes)
	{
		RRMLib::DrawBox(h.rc.Left(), h.rc.Top(), h.rc.Right(), h.rc.Bottom(), 0xffffffff, false);
	}
}

void
PlayerHitBox::Clear()
{
	_hitboxes.clear();
}

std::vector<HitBox>& 
PlayerHitBox::GetHitBoxes()
{
	return _hitboxes;
}