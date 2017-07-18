#include "Hamburger.h"
#include <RRMLib.h>

static const int IMG_NUM = 9;
static const float IMG_W = 64.f;
static const float IMG_H = 64.f;

static const float ENEMY_SIZE = 256.f;

static const float ANIM_SPEED = 0.2f;

Hamburger::Hamburger(int handle, const Position& pos)
{
	_handle = handle;
	_rc.pos = pos;
	_rc.w = ENEMY_SIZE;
	_rc.h = ENEMY_SIZE;

	_dis = Distance::d_near;
	_disUpdate[Distance::d_near] = &Hamburger::NearUpdate;
	_disUpdate[Distance::d_medium] = &Hamburger::MediumUpdate;
	_disUpdate[Distance::d_far] = &Hamburger::FarUpdate;

	_state = State::avoidance;
	_stateUpdate[State::aplysia] = &Hamburger::Aplysia;
	_stateUpdate[State::avoidance] = &Hamburger::Avoidance;
	_stateUpdate[State::jump_avoid] = &Hamburger::JumpAvoid;
	_stateUpdate[State::melee_attack] = &Hamburger::MeleeAttack;
	_stateUpdate[State::normal_bullet] = &Hamburger::NormalBullet;
	_stateUpdate[State::shock_wave] = &Hamburger::ShockWave;
	_stateUpdate[State::summon] = &Hamburger::Summon;
	_stateUpdate[State::wait] = &Hamburger::Wait;
}

Hamburger::~Hamburger()
{
}

void
Hamburger::Initialize()
{

}

void
Hamburger::Anim()
{
	static const Vector2 UV[IMG_NUM]
	{
		Vector2(IMG_W * 0, IMG_H * 0),
		Vector2(IMG_W * 1, IMG_H * 0),
		Vector2(IMG_W * 2, IMG_H * 0),
		Vector2(IMG_W * 3, IMG_H * 0),
		Vector2(IMG_W * 4, IMG_H * 0),
		Vector2(IMG_W * 0, IMG_H * 1),
		Vector2(IMG_W * 1, IMG_H * 1),
		Vector2(IMG_W * 2, IMG_H * 1),
		Vector2(IMG_W * 3, IMG_H * 1),
	};

	++_animFrame;
	int idx = (int)(_animFrame * ANIM_SPEED) % IMG_NUM;
	_uv = UV[idx];
}


void 
Hamburger::NearUpdate()
{
	(this->*_stateUpdate[_state])();
}

void
Hamburger::MediumUpdate()
{
	(this->*_stateUpdate[_state])();
}

void 
Hamburger::FarUpdate()
{
	(this->*_stateUpdate[_state])();
}

void 
Hamburger::Avoidance()
{

}

void 
Hamburger::JumpAvoid()
{

}

void 
Hamburger::MeleeAttack()
{

}

void 
Hamburger::Wait()
{

}

void 
Hamburger::ShockWave()
{

}

void 
Hamburger::Aplysia()
{

}

void 
Hamburger::NormalBullet()
{

}

void 
Hamburger::Summon()
{

}

void 
Hamburger::Update()
{
	Gravity();
	Anim();
	_rc.pos += _vel;

	(this->*_disUpdate[_dis])();

}

void 
Hamburger::Draw(const Position& offset)
{
	Position drawPos;
	drawPos.x = _rc.pos.x - offset.x;
	drawPos.y = _rc.pos.y - offset.y;

	RRMLib::DrawRectExtendGraph(drawPos.x, drawPos.y, drawPos.x + _rc.w, drawPos.y + _rc.h,
		_uv.x, _uv.y, IMG_W, IMG_H, _handle, true, false);
}

