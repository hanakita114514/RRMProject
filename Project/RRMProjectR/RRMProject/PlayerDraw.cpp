#include "PlayerDraw.h"
#include <RRMLib.h>

static const float IMG_H = 234.5f;
static const float IMG_W = 158.f;

PlayerDraw::PlayerDraw(const Rect& rc, const Vector2& dir)
	: _playerRc(rc), _dir(dir)
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


	_handleMap[PlayerState::neutral] = RRMLib::LoadGraph("Resource/img/player/lanstar/neutral.png");
	_handleMap[PlayerState::walk] = RRMLib::LoadGraph("Resource/img/player/lanstar/dash.png");
	_handleMap[PlayerState::attack] = RRMLib::LoadGraph("Resource/img/player/lanstar/attack.png");
	_handleMap[PlayerState::jump] = RRMLib::LoadGraph("Resource/img/player/lanstar/jump.png");
	_handleMap[PlayerState::damage] = RRMLib::LoadGraph("Resource/img/player/lanstar/damage.png");
	_handleMap[PlayerState::die] = RRMLib::LoadGraph("Resource/img/player/lanstar/die.png");

	_frame = 0;
}


PlayerDraw::~PlayerDraw()
{
}

void 
PlayerDraw::NeutralDraw(const Vector2& pos)
{
	static const int ANIM_NUM = 6;
	static Vector2 UV[ANIM_NUM]
	{
		Vector2(IMG_W * 0 , IMG_H * 0),
		Vector2(IMG_W * 1 , IMG_H * 0),
		Vector2(IMG_W * 2 , IMG_H * 0),
		Vector2(IMG_W * 3 , IMG_H * 0),
		Vector2(IMG_W * 4 , IMG_H * 0),
		Vector2(IMG_W * 5 , IMG_H * 0),
	};

	int idx = (int)(_frame * 0.5f) % ANIM_NUM;
	_uv = UV[idx];

	RRMLib::DrawRectExtendGraph(pos.x, pos.y, pos.x + _playerRc.w, pos.y + _playerRc.h,
		_uv.x, _uv.y, IMG_W, IMG_H, _handleMap[PlayerState::neutral], true, _dir.x > 0);
}

void 
PlayerDraw::WalkDraw(const Vector2& pos)
{
	static const int ANIM_NUM = 6;
	static Vector2 UV[ANIM_NUM]
	{
		Vector2(IMG_W * 0 , IMG_H * 0),
		Vector2(IMG_W * 1 , IMG_H * 0),
		Vector2(IMG_W * 2 , IMG_H * 0),
		Vector2(IMG_W * 3 , IMG_H * 0),
		Vector2(IMG_W * 4 , IMG_H * 0),
		Vector2(IMG_W * 5 , IMG_H * 0),
	};

	int idx = (int)(_frame * 0.12f) % ANIM_NUM;
	_uv = UV[idx];
	++_frame;

	RRMLib::DrawRectExtendGraph(pos.x, pos.y, pos.x + _playerRc.w, pos.y + _playerRc.h,
		_uv.x, _uv.y, IMG_W, IMG_H, _handleMap[PlayerState::walk], true, _dir.x > 0);
}
void 
PlayerDraw::AvoidanceDraw(const Vector2& pos)
{
	static const int ANIM_NUM = 1;
	static Vector2 UV[ANIM_NUM]
	{
		Vector2(IMG_W * 4 , IMG_H * 0),
	};

	int idx = (int)(_frame * 0.12f) % ANIM_NUM;
	_uv = UV[idx];

	RRMLib::DrawRectExtendGraph(pos.x, pos.y, pos.x + _playerRc.w, pos.y + _playerRc.h,
		_uv.x, _uv.y, IMG_W, IMG_H, _handleMap[PlayerState::walk], true, _dir.x > 0);
}

void 
PlayerDraw::AttackDraw(const Vector2& pos)
{
	RRMLib::DrawRectExtendGraph(pos.x, pos.y, pos.x + _playerRc.w, pos.y + _playerRc.h,
		0, 0, IMG_W, IMG_H, _handleMap[PlayerState::attack], true, _dir.x > 0);
}

void
PlayerDraw::InvincibleDraw(const Vector2& pos)
{
	static const int ANIM_NUM = 2;
	static Vector2 UV[ANIM_NUM]
	{
		Vector2(IMG_W * 0 , IMG_H * 0),
		Vector2(IMG_W * 1 , IMG_H * 0),
	};

	int idx = (int)(_frame * 0.12f) % ANIM_NUM;
	_uv = UV[idx];
	++_frame;


	if ((_frame / 3) % 2 == 0)
	{
		RRMLib::DrawRectExtendGraph(pos.x, pos.y, pos.x + _playerRc.w, pos.y + _playerRc.h,
			_uv.x, _uv.y, IMG_W, IMG_H, _handleMap[PlayerState::damage], true, _dir.x > 0);
	}
	++_frame;
}
void 
PlayerDraw::DamageDraw(const Vector2& pos)
{
	static const int ANIM_NUM = 2;
	static Vector2 UV[ANIM_NUM]
	{
		Vector2(IMG_W * 0 , IMG_H * 0),
		Vector2(IMG_W * 1 , IMG_H * 0),
	};

	int idx = (int)(_frame * 0.12f) % ANIM_NUM;
	_uv = UV[idx];
	++_frame;

	RRMLib::DrawRectExtendGraph(pos.x, pos.y, pos.x + _playerRc.w, pos.y + _playerRc.h,
		_uv.x, _uv.y, IMG_W, IMG_H, _handleMap[PlayerState::damage], true, _dir.x > 0);
}
void 
PlayerDraw::DieDraw(const Vector2& pos)
{

}
void 
PlayerDraw::JumpDraw(const Vector2& pos)
{
	static const int ANIM_NUM = 3;
	static Vector2 UV[ANIM_NUM]
	{
		Vector2(IMG_W * 0 , IMG_H * 0),
		Vector2(IMG_W * 1 , IMG_H * 0),
		Vector2(IMG_W * 2 , IMG_H * 0),
	};

	int idx = (int)(_frame * 0.12f) % ANIM_NUM;
	_uv = UV[idx];
	++_frame;

	RRMLib::DrawRectExtendGraph(pos.x, pos.y, pos.x + _playerRc.w, pos.y + _playerRc.h,
		_uv.x, _uv.y, IMG_W, IMG_H, _handleMap[PlayerState::jump], true, _dir.x > 0);
}
void 
PlayerDraw::ShootDraw(const Vector2& pos)
{
	RRMLib::DrawRectExtendGraph(pos.x, pos.y, pos.x + _playerRc.w, pos.y + _playerRc.h,
		0, 0, IMG_W, IMG_H, _handleMap[PlayerState::attack], true, _dir.x > 0);
}

void
PlayerDraw::Draw(const Vector2& pos, const PlayerState& state)
{
	(this->*_draw[state])(pos);
}