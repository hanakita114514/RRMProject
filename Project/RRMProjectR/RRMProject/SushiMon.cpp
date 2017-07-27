#include "SushiMon.h"
#include <RRMLib.h>
#include "GameTime.h"
#include "EffectManager.h"
#include "SushiHitBox.h"

static const int MAX_HP = 100;

static const int IMG_MAX = 2;

SushiMon::SushiMon(int handle , const Position& pos)
{
	_friction = 0.05f;
	_handle = handle;
	_rc.pos = pos;
	_hp.SetMaxHp(MAX_HP);
	_hp.FullRecovery();

	_rc.w = 64;
	_rc.h = 32;

	_dir = Vector2(-1, 0);
	_uv = Vector2(0, 0);
	_vel.x = _dir.x * 2;

	_update[UpdateState::fall] = &SushiMon::FallUpdate;
	_update[UpdateState::alive] = &SushiMon::AliveUpdate;
	_update[UpdateState::attack] = &SushiMon::AttackUpdate;
	_update[UpdateState::damage] = &SushiMon::DamageUpdate;
	_update[UpdateState::dying] = &SushiMon::DyingUpdate;
	_update[UpdateState::search] = &SushiMon::SearchUpdate;
	_update[UpdateState::worry] = &SushiMon::WorryUpdate;
	_update[UpdateState::charge] = &SushiMon::ChargeUpdate;
	_state = UpdateState::fall;

	_animFrame = 0;

	_hitBox = new SushiHitBox();
	_footCheck = true;
	_warryTime = 0.0f;
	_chargeTime = 0.0f;
	_searchTime = 0.0f;
}


SushiMon::~SushiMon()
{
	delete _hitBox;
}

void 
SushiMon::Initialize()
{

}

void 
SushiMon::AliveUpdate()
{
	Gravity();
	_vel.x = _dir.x * 2 * GameTime::Instance().GetTimeScale(this);

	_rc.pos += _vel;
	_hitBox->Foot(0, _rc, _dir);
	_hitBox->Search(0, _rc, _dir);

	_hpbar.CommitPeriod();

	if (!_footCheck)
	{
		_state = UpdateState::worry;
		_warryTime = 5;
	}

	if (_isSearch)
	{
		_state = UpdateState::search;
		_searchTime = 20.f;
		_hitBox->SearchClear();
		//‰EŒü‚«
		if (_targetPos.x > _rc.pos.x)
		{
			_dir.x = 1;
		}
		else
		{
			_dir.x = -1;
		}
	}

	if (_isDamage)
	{
		_state = UpdateState::damage;
	}

	if (_hp.IsDead())
	{
		_state = UpdateState::dying;
		EffectManager::Instance().Create(EffectType::erasure, _rc.Center(), Vector2(1.5f, 1.5f), 1.3f);
		_isAlive = false;
	}
}

void 
SushiMon::DyingUpdate()
{

}

void
SushiMon::ChargeUpdate()
{
	--_chargeTime;

	static int quake = 1;

	_rc.pos.x = _rc.pos.x + (3 * quake);
	quake *= -1;

	if (_chargeTime < 0)
	{
		_state = UpdateState::attack;

		_vel.x = _dir.x * 4.f;
		_vel.y = -13;
	}
}

void 
SushiMon::SearchUpdate()
{
	Gravity();
	_vel.x = _dir.x * 4.f * GameTime::Instance().GetTimeScale(this);
	_rc.pos += _vel;

	--_searchTime;

	if (_searchTime < 0 && _hitGround)
	{
		_state = UpdateState::charge;
		_chargeTime = 30.0f;
		_hitBox->Foot(0, _rc, _dir);
		_hitBox->Search(0, _rc, _dir);
	}
}

void
SushiMon::AttackUpdate()
{
	Gravity();
	_rc.pos += _vel;
	_hitBox->Attack(0, _rc, _dir);

	if (_hitGround)
	{
		_state = UpdateState::alive;
		
		_isSearch = false;
		_hitBox->Clear();
		_mhp.Clear();
	}
}

void 
SushiMon::WorryUpdate()
{
	--_warryTime;

	if (_warryTime <= 0)
	{
		_state = UpdateState::fall;

		_dir.x *= -1;
		_vel.x = _dir.x * 2;
		_hitBox->Foot(0, _rc, _dir);
		_hitBox->Search(0, _rc, _dir);
	}
}

void 
SushiMon::FallUpdate()
{
	Gravity();
	_rc.pos += _vel;
	if (_hitGround)
	{
		_state = UpdateState::alive;
	}
}

void 
SushiMon::DamageUpdate()
{
	Gravity();
	_rc.pos += _vel;

	DistanceAttenuation();

	if (_vel.x == 0)
	{
		_isDamage = false;
		_state = UpdateState::alive;
		_vel.x = _dir.x * 2;
		_hpbar.Commit();
		_armor.Recovery();
	}
}

void 
SushiMon::Update()
{
	if (!_hitStop.IsHitStop())
	{
		Anim();
		(this->*_update[_state])();
	}
	if (_armor.IsBroken())
	{
	}
	_hpbar.Update();
	_hitStop.Update();
}

void 
SushiMon::Draw(const Vector2& offset)
{
	Vector2 drawPos;
	drawPos.x = _rc.pos.x - offset.x;
	drawPos.y = _rc.pos.y - offset.y;

	RRMLib::DrawRectGraph(drawPos.x, drawPos.y, _uv.x, _uv.y, _rc.w, _rc.h, _handle, true, _dir.x > 0);
	_hpbar.Draw(Vector2(drawPos.x + _rc.w / 4, drawPos.y - _rc.h / 4), _hp);

	//ColDraw();
}

void 
SushiMon::Anim()
{
	static const Vector2 uv[]
	{
		Vector2(0,0),
		Vector2(_rc.w, 0)
	};

	_animFrame += GameTime::Instance().GetTimeScale(this);

	int idx = (int)(_animFrame * 0.1f) % IMG_MAX;

	_uv = uv[idx];
}

EnemyType 
SushiMon::GetEnemyType()
{
	return EnemyType::sushi;
}