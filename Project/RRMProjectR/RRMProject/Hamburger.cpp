#include "Hamburger.h"
#include <RRMLib.h>
#include "AbstractSpell.h"
#include <math.h>
#include <time.h>
#include "EnemyManager.h"
#include "GameTime.h"
#include "BurgerHitBox.h"

static const int IMG_NUM = 9;
static const float IMG_W = 64.f;
static const float IMG_H = 64.f;

static const float ENEMY_SIZE = 256.f;

static const float ANIM_SPEED = 0.2f;

static const int WAIT_TIME = 60;


Hamburger::Hamburger(int handle, const Position& pos, const Position& playerPos, Camera& camera) : _playerPos(playerPos), _camera(camera)
{
	_handle = handle;
	_rc.pos = pos; 
	_rc.w = ENEMY_SIZE;
	_rc.h = ENEMY_SIZE;

	_dis = Distance::d_near;
	_disUpdate[Distance::d_near] = &Hamburger::NearUpdate;
	_disUpdate[Distance::d_medium] = &Hamburger::MediumUpdate;
	_disUpdate[Distance::d_far] = &Hamburger::FarUpdate;

	_state = State::aplysia;
	_stateUpdate[State::aplysia] = &Hamburger::Aplysia;
	_stateUpdate[State::avoidance] = &Hamburger::Avoidance;
	_stateUpdate[State::jump_avoid] = &Hamburger::JumpAvoid;
	_stateUpdate[State::melee_wait] = &Hamburger::MeleeWait;
	_stateUpdate[State::melee_attack] = &Hamburger::MeleeAttack;
	_stateUpdate[State::normal_bullet] = &Hamburger::NormalBullet;
	_stateUpdate[State::shock_wave] = &Hamburger::ShockWave;
	_stateUpdate[State::summon] = &Hamburger::Summon;
	_stateUpdate[State::near_wait] = &Hamburger::NearWait;
	_stateUpdate[State::middle_wait] = &Hamburger::MiddleWait;
	_stateUpdate[State::far_wait] = &Hamburger::FarWait;
	_stateUpdate[State::none] = &Hamburger::None;
	_stateUpdate[State::stroll] = &Hamburger::Stroll;

	_update = Update::alive;
	_updateFunc[Update::alive] = &Hamburger::AliveUpdate;
	_updateFunc[Update::damage] = &Hamburger::DamageUpdate;
	_updateFunc[Update::dying] = &Hamburger::DyingUpdate;


	_spell = _absSpell->GetSpell(SpellType::RainSpell);

	_waitFrame = 0.f;
	_strollTime = 0.f;
	_aplysiaTime = 0.f;
	_meleeTime = 0.f;

	srand(time(NULL));

	_dir = 0;

	_hp.SetMaxHp(1000);
	_hp.FullRecovery();

	_hitBox = new BurgerHitBox();
}

Hamburger::~Hamburger()
{
	delete _hitBox;
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

	if (_waitFrame == 0)
	{
		_state = State::near_wait;
	}
}

void
Hamburger::MediumUpdate()
{
	(this->*_stateUpdate[_state])();
	if (_waitFrame == 0)
	{
		_state = State::middle_wait;
	}
}

void 
Hamburger::FarUpdate()
{
	(this->*_stateUpdate[_state])();

	if (_waitFrame == 0)
	{
		_state = State::far_wait;
	}
}

void 
Hamburger::Avoidance()
{
	_vel.x = -_dir * 20;
	_waitFrame = 0;
}

void 
Hamburger::JumpAvoid()
{
	_vel.x = -_dir * 14;
	_vel.y = -15;
	_waitFrame = 0;
}

void 
Hamburger::MeleeWait()
{
	static const int TIME = 60;
	static int QUAKE = 1;

	_rc.pos.x += QUAKE * 10;
	QUAKE *= -1;

	if (_meleeTime >= TIME)
	{
		_vel.x = _dir * 15;
		_state = State::melee_attack;
		_meleeTime = 0.f;
	}
	++_meleeTime;
}

void 
Hamburger::MeleeAttack()
{
	static const int TIME = 30;

	_hitBox->Attack(0, _rc, Vector2(_dir, 0));

	if (_meleeTime >= TIME)
	{
		_mhp.Clear();
		_hitBox->Clear();
		_waitFrame = 0;
		_meleeTime = 0;
	}
	++_meleeTime;
}

void 
Hamburger::NearWait()
{
	static const int STATE = 4;
	static const int AVOID = 0;
	static const int JUMP_AVOID = 1;
	static const int MELEE_ATK = 2;
	static const int BULLET = 3;

	_waitFrame++;

	if (_waitFrame < WAIT_TIME)
	{
		return;
	}

	int r = rand() % STATE;

	switch (r)
	{
	case AVOID:
		_state = State::avoidance;
		break;
	case JUMP_AVOID:
		_state = State::jump_avoid;
		break;
	case MELEE_ATK:
		_state = State::melee_wait;
		break;
	case BULLET:
		_state = State::normal_bullet; 
		break;
	default:
		break;
	}
}

void
Hamburger::MiddleWait()
{
	static const int STATE = 3;
	static const int BULLET = 0;
	static const int STROLL = 1;
	static const int SHOCK_WAVE = 2;

	_waitFrame++;

	if (_waitFrame < WAIT_TIME)
	{
		return;
	}

	int r = rand() % STATE;

	switch (r)
	{
	case BULLET:
		_state = State::normal_bullet;
		break;
	case STROLL:
		_state = State::stroll;
		break;
	case SHOCK_WAVE:
		_state = State::shock_wave;
		break;
	default:
		break;
	}
}

void
Hamburger::FarWait()
{
	static const int STATE = 4;
	static const int SUMMON = 0;
	static const int APLYSIA = 1;
	static const int BULLET = 2;
	static const int STROLL = 3;

	_waitFrame++;

	if (_waitFrame < WAIT_TIME)
	{
		return;
	}

	int r = rand() % STATE;

	switch (r)
	{
	case SUMMON:
		_state = State::summon;
		break;
	case APLYSIA:
		_state = State::aplysia;
		break;
	case BULLET:
		_state = State::normal_bullet;
		break;
	case STROLL:
		_state = State::stroll;
		break;
	default:
		break;
	}
}

void 
Hamburger::Stroll()
{
	static const int STR_TIME = 60;

	_vel.x = _dir * 8;

	if (_strollTime >= STR_TIME)
	{
		_waitFrame = 0;
		_strollTime = 0;
	}
	++_strollTime;
}

void 
Hamburger::ShockWave()
{
	_waitFrame = 0;
}

void
Hamburger::None()
{

}

void 
Hamburger::Aplysia()
{
	if (_aplysiaTime++ == 0)
	{
		_vel.y = -20;
		return;
	}

	if (_hitGround)
	{
		_spell = _absSpell->GetSpell(SpellType::RainSpell);
		_spell->Create(Vector2(0, 0), Position(0, 0), this);
		_state = State::none;
		_waitFrame = 0;
		_aplysiaTime = 0;
		_camera.Quake(Vector2(0, 6));
	}
}

void 
Hamburger::NormalBullet()
{
	_spell = _absSpell->GetSpell(SpellType::TestSpell);
	_spell->Create(Vector2(_dir,0), _rc.Center(), this);
	_waitFrame = 0;
}

void 
Hamburger::Summon()
{
	EnemyManager::Instance().AddList(EnemyType::meat, _rc.Center());
	_waitFrame = 0;
}

void 
Hamburger::AliveUpdate()
{
	Anim();
	_rc.pos += _vel * GameTime::Instance().GetTimeScale(this);
	Gravity();
	Enemy::DistanceAttenuation();

	float distance;
	distance = abs(_playerPos.x - _rc.Center().x);
	_dir = _playerPos.x - _rc.Center().x;

	if (_dir > 0)
	{
		_dir = 1;
	}
	else
	{
		_dir = -1;
	}

	(this->*_disUpdate[_dis])();


	if (distance >= 500)
	{
		_dis = Distance::d_far;
	}
	else if (distance >= 300)
	{
		_dis = Distance::d_medium;
	}
	else if (distance >= 0)
	{
		_dis = Distance::d_near;
	}

	if (_hp.IsDead())
	{
		_update = Update::dying;
	}
}

void 
Hamburger::DamageUpdate()
{

}

void 
Hamburger::DyingUpdate()
{
	_isAlive = false;

}

void 
Hamburger::Update()
{
	(this->*_updateFunc[_update])();


}

void 
Hamburger::Draw(const Position& offset)
{
	Position drawPos;
	drawPos.x = _rc.pos.x - offset.x;
	drawPos.y = _rc.pos.y - offset.y;

	RRMLib::DrawRectExtendGraph(drawPos.x, drawPos.y, drawPos.x + _rc.w, drawPos.y + _rc.h,
		_uv.x, _uv.y, IMG_W, IMG_H, _handle, true, false);

	_hpbar.Draw(Position(drawPos.x + _rc.w / 2, drawPos.y), _hp);

	//ColDraw();
}

