#include "PlayerDraw.h"
#include <RRMLib.h>

PlayerDraw::PlayerDraw()
{
	_draw[PlayerState::attack] = &PlayerDraw::AttackDraw;
	_draw[PlayerState::neutral] = &PlayerDraw::NeutralDraw;
	_draw[PlayerState::walk] = &PlayerDraw::WalkDraw;
	_draw[PlayerState::avoidance] = &PlayerDraw::AvoidanceDraw;
	_draw[PlayerState::jump] = &PlayerDraw::JumpDraw;
	_draw[PlayerState::invincible] = &PlayerDraw::InvincibleDraw;
	_draw[PlayerState::damage] = &PlayerDraw::DamageDraw;
	_draw[PlayerState::die] = &PlayerDraw::DieDraw;
	_draw[PlayerState::shoot] = &PlayerDraw::ShootDraw;


	_handleMap[PlayerState::neutral] = RRMLib::LoadGraph("Resource/img/player/player.png");
	_handleMap[PlayerState::attack] = RRMLib::LoadGraph("Resource/img/player/attack.png");
	_handleMap[PlayerState::avoidance] = RRMLib::LoadGraph("Resource/img/player/avoidance.png");

	_frame = 0;
}


PlayerDraw::~PlayerDraw()
{
}

void 
PlayerDraw::NeutralDraw(const Vector2& pos)
{
	RRMLib::DrawGraph(pos.x, pos.y, _handleMap[PlayerState::neutral]);
}

void 
PlayerDraw::WalkDraw(const Vector2& pos)
{
	RRMLib::DrawGraph(pos.x, pos.y, _handleMap[PlayerState::neutral]);
}
void 
PlayerDraw::AvoidanceDraw(const Vector2& pos)
{
	RRMLib::DrawGraph(pos.x, pos.y, _handleMap[PlayerState::avoidance]);
}

void 
PlayerDraw::AttackDraw(const Vector2& pos)
{
	RRMLib::DrawGraph(pos.x, pos.y, _handleMap[PlayerState::attack]);

}

void
PlayerDraw::InvincibleDraw(const Vector2& pos)
{
	if ((_frame / 3) % 2 == 0)
	{
		RRMLib::DrawGraph(pos.x, pos.y, _handleMap[PlayerState::neutral]);
	}
	++_frame;
}
void 
PlayerDraw::DamageDraw(const Vector2& pos)
{
	RRMLib::DrawGraph(pos.x, pos.y, _handleMap[PlayerState::neutral]);
}
void 
PlayerDraw::DieDraw(const Vector2& pos)
{

}
void 
PlayerDraw::JumpDraw(const Vector2& pos)
{
	//RRMLib::DrawRectGraph(pos.x, pos.y, ((_animFrame / 6) % 4) * 144, 96 * 1, 144, 96, _handleMap[PlayerState::neutral], true, _turnFlag);
	RRMLib::DrawGraph(pos.x, pos.y, _handleMap[PlayerState::neutral]);
}
void 
PlayerDraw::ShootDraw(const Vector2& pos)
{
	RRMLib::DrawGraph(pos.x, pos.y, _handleMap[PlayerState::attack]);
}

void
PlayerDraw::Draw(const Vector2& pos, const PlayerState& state)
{
	(this->*_draw[state])(pos);
}