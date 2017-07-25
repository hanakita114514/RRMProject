#include "Meat.h"
#include "EffectManager.h"
#include <RRMLib.h>
#include "GameTime.h"
#include "MeatHitBox.h"

const int ENEMY_SIZE_X = 64;
const int ENEMY_SIZE_Y = 32;
const int IMAGE_NUM = 4;
const int DEFAULT_COOL_TIME = 60;
const int MEAT_TERRITORY_X = 300;
const int MEAT_TERRITORY_Y = 32;

Meat::Meat()
{

}

Meat::Meat(int handle, Vector2 pos)
{
	_handle = handle;

	_update = &Meat::AlliveUpdate;
	_meatState = State::wait;
	_animCnt = 0;
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

	_hitBox->Search(0, _rc, _dir);
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

	if (_isSearch)
	{
		EffectManager::Instance().Create(EffectType::exclamation, _rc.pos + Vector2(_rc.w / 2, _rc.h / 2 * -1),
											Vector2(0.5,0.5),10.0f);
		_meatState = State::find;
	}

	Move();

	_territory.Update(_rc);

	if (_territory.IsOutRange())
	{
		_dir.x *= -1;
		_territory.InRange();
		_rc.pos.x += 5 * _dir.x;
	}

	Anim();
}

void Meat::Find()
{
	if (!_isSearch)
	{
		_meatState = State::coolTime;
		_coolCnt = DEFAULT_COOL_TIME;
	}
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
}

void Meat::Anim()
{
	const Vector2 animUV[IMAGE_NUM] =
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
	_vel.x = 5 * _dir.x;

	_rc.pos += _vel* GameTime::Instance().GetTimeScale(this);
	_vel.x = 0;
}

void Meat::Draw(const Vector2& offset)
{
	float drawPosX = _rc.pos.x - offset.x;
	float drawPosY = _rc.pos.y - offset.y;
	RRMLib::DrawRectGraph(drawPosX, drawPosY, _uv.x, _uv.y,
							ENEMY_SIZE_X, ENEMY_SIZE_Y, _handle, true, false);
	_hpbar.Draw(Position(drawPosX + _rc.w / 4, drawPosY - _rc.h / 4), _hp);
