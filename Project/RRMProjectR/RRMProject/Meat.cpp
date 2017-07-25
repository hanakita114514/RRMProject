#include "Meat.h"
#include "EffectManager.h"
#include <RRMLib.h>
#include "GameTime.h"
#include "MeatHitBox.h"
#include "Mathematics.h"

const int ENEMY_SIZE_X = 64;
const int ENEMY_SIZE_Y = 32;
const int IMAGE_NUM = 4;
const int DEFAULT_COOL_TIME = 60;
const int MEAT_TERRITORY_X = 300;
const int MEAT_TERRITORY_Y = 32;
const int MEAT_ATTACK_WAIT = 15;
const int MEAT_FIND_WAIT = 20;
const int MEAT_MOVE_SPEED = 5;

const float MEAT_ATTACK_RANGE = 12.0f;

Meat::Meat()
{

}

Meat::Meat(int handle, Vector2 pos)
{
	_handle = handle;

	_update = &Meat::AlliveUpdate;
	_meatState = State::wait;
	_animCnt = 0;
	_frameCnt = 0;
	_hitGround = false;
	_isSearch = false;

	Rect rc = {};
	rc.pos = pos;
	rc.h = ENEMY_SIZE_Y;
	rc.w = ENEMY_SIZE_X;

	_rc = rc;
	_vel = Vector2(0, 0);
	_dir = Vector2(-1, 0);
	_isAlive = true;

	_hitBox = new MeatHitBox();
	_territory.Set(MEAT_TERRITORY_X, MEAT_TERRITORY_Y, _rc.pos);

	_coolCnt = 0;
	_isPlayEffect = false;
}

Meat::~Meat()
{
}

void Meat::Initialize()
{

}

void Meat::Update()
{
	(this->*_update)();
}

void Meat::AlliveUpdate()
{
	(this->*_state[(int)_meatState])();

	if (_isDamage)
	{
		_update = &Meat::DamageUpdate;
	}

	_hpbar.CommitPeriod();

	if (_hp.GetHitPoint() <= 0)
	{
		_update = &Meat::DyingUpdate;
		EffectManager::Instance().Create(EffectType::erasure, _rc.Center());
		_isAlive = false;
	}
}

void Meat::DamageUpdate()
{
	DistanceAttenuation();

	if (_hitGround)
	{
		_vel.y = 0;
		_animCnt += GameTime::Instance().GetTimeScale(this);
	}

	Gravity();

	_rc.pos += _vel * GameTime::Instance().GetTimeScale(this);
	if (_vel.x == 0)
	{
		_isDamage = false;
		_territory.Set(MEAT_TERRITORY_X, MEAT_TERRITORY_Y, _rc.pos);
		_update = &Meat::AlliveUpdate;
	}

	_hpbar.Commit();
}

void
Meat::DyingUpdate()
{

}

void Meat::Wait()
{
	if (_hitGround)
	{
		_animCnt += GameTime::Instance().GetTimeScale(this);
	}

	Gravity();
	_hitBox->Search(0, _rc, _dir);

	if (_isSearch)
	{
		EffectManager::Instance().Create(EffectType::exclamation, _rc.pos + Vector2(_rc.w / 2, _rc.h / 2 * -1),
											Vector2(0.5,0.5),10.0f);
		_meatState = State::find;
		_vel.x = -1;
	}

	Move();
	Anim();
}

void
Meat::Jump()
{
	_vel.y = -10;
}

void Meat::Find()
{
	if (!_isSearch)
	{
		_meatState = State::coolTime;
		_coolCnt = DEFAULT_COOL_TIME;
		_frameCnt = 0;
	}
	_hitBox->Search(0, _rc, _dir);

	_rc.pos += _vel;
	_vel.x = -1;

	_frameCnt++;
	if (_frameCnt > MEAT_FIND_WAIT)
	{
		_meatState = State::attack;
		_vel.x = MEAT_ATTACK_RANGE * _dir.x;
		_frameCnt = 0;
	}
	Anim();
}

void Meat::Attack()
{
	++_frameCnt;

	if (_frameCnt == MEAT_ATTACK_WAIT)
	{
		_rc.pos += _vel;
		if (_dir.x > 0)
		{
			--_vel.x;
		}
		else
		{
			++_vel.x;
		}
		_frameCnt--;
	}

	_hitBox->Attack(0, _rc, _dir);

	if (_vel.x == 0)
	{
		_meatState = State::coolTime;
		_territory.Set(300, 32, _rc.pos);
		_isPlayEffect = true;
		_hitBox->Clear();
		_coolCnt = DEFAULT_COOL_TIME;
		_mhp.Clear();
		_frameCnt = 0;
	}

	_isSearch = false;

	Anim();
}

void Meat::CoolTime()
{
	if (!_isPlayEffect)
	{
		EffectManager::Instance().Create(EffectType::question, _rc.pos + Vector2(_rc.w / 2, _rc.h / 2 * -1),
			Vector2(0.5, 0.5), 10.0f);
		_isPlayEffect = true;
	}

	--_coolCnt;
	if (_coolCnt < 0)
	{
		_meatState = State::wait;
		_isPlayEffect = false;
	}

	_isSearch = false;

	Move();

	Anim();
}

void Meat::Anim()
{
	static const Vector2 animUV[IMAGE_NUM] =
	{
		Vector2(ENEMY_SIZE_X * 0,0),
		Vector2(ENEMY_SIZE_X * 1, 0),
		Vector2(ENEMY_SIZE_X * 2, 0),
		Vector2(ENEMY_SIZE_X * 3, 0),
	};

	int animFrame = (int)_animCnt * 0.2f;

	_uv = animUV[animFrame % IMAGE_NUM];
}

void Meat::Move()
{
	_vel.x = MEAT_MOVE_SPEED * _dir.x;

	_rc.pos += _vel* GameTime::Instance().GetTimeScale(this);

	_territory.Update(_rc);

	if (_territory.IsOutRange())
	{
		_dir.x *= -1;
		_territory.InRange();
		_rc.pos.x += MEAT_MOVE_SPEED * _dir.x;
	}
	_vel.x = 0;
}

void Meat::Draw(const Vector2& offset)
{
	float drawPosX = _rc.pos.x - offset.x;
	float drawPosY = _rc.pos.y - offset.y;
	RRMLib::DrawRectGraph(drawPosX, drawPosY, _uv.x, _uv.y,
							ENEMY_SIZE_X, ENEMY_SIZE_Y, _handle, true, false);
	_hpbar.Draw(Position(drawPosX + _rc.w / 4, drawPosY - _rc.h / 4), _hp);
void
Meat::SearchHit(const Position& targetPos)
{
	_targetPos = targetPos;
	_isSearch = true;
}

void
Meat::SearchFailed()
{
	_isSearch = false;
