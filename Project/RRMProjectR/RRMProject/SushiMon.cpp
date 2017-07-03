#include "SushiMon.h"
#include <RRMLib.h>
#include "GameTime.h"
#include "EffectManager.h"
#include "SushiHitBox.h"

static const int MAX_HP = 200;

static const int IMG_MAX = 2;

SushiMon::SushiMon(int handle , const Position& pos)
{
	_friction = 0.1f;
	_handle = handle;
	_rc.pos = pos;
	_hp.SetMaxHp(MAX_HP);
	_hp.FullRecovery();

	_rc.w = 64;
	_rc.h = 32;

	_dir = Vector2(-1, 0);
	_uv = Vector2(0, 0);
	_vel.x = _dir.x * 2;

	_update = &SushiMon::FallUpdate;

	_animFrame = 0;

	_hitBox = new SushiHitBox();
	_footCheck = true;
	_warryTime = 0.0f;
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
	_rc.pos += _vel;
	_hitBox->Foot(0, _rc, _dir);

	if (!_footCheck)
	{
		_update = &SushiMon::WorryUpdate;
		_warryTime = 10;
	}
	if (_isDamage)
	{
		_update = &SushiMon::DamageUpdate;
	}

	if (_hp.GetHitPoint() <= 0)
	{
		_update = &SushiMon::DyingUpdate;
		EffectManager::Instance().Create(EffectType::erasure, _rc.Center(), Vector2(1.5f, 1.5f), 1.3f);
		_isAlive = false;
	}
}

void 
SushiMon::DyingUpdate()
{

}

void 
SushiMon::WorryUpdate()
{
	--_warryTime;

	if (_warryTime <= 0)
	{
		_update = &SushiMon::FallUpdate;
		_vel.y = -15;
		_vel.x = _dir.x * 8;
	}
}

void 
SushiMon::FallUpdate()
{
	Gravity();
	_rc.pos += _vel;
	if (_hitGround)
	{
		_update = &SushiMon::AliveUpdate;
		_footCheck = true;
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
		_update = &SushiMon::AliveUpdate;
		_vel.x = _dir.x * 2;
	}
}

void 
SushiMon::Update()
{
	Anim();
	(this->*_update)();
}

void 
SushiMon::Draw(const Vector2& offset)
{
	Vector2 drawPos;
	drawPos.x = _rc.pos.x - offset.x;
	drawPos.y = _rc.pos.y - offset.y;

	RRMLib::DrawRectGraph(drawPos.x, drawPos.y, _uv.x, _uv.y, _rc.w, _rc.h, _handle, true, _dir.x > 0);
	_hpbar.Draw(Vector2(drawPos.x + _rc.w / 4, drawPos.y - _rc.h / 4), _hp);

	for (auto& s : _hitBox->GetSearchRects())
	{
		s.DrawBox();
	}
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