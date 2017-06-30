#include "SushiMon.h"
#include <RRMLib.h>
#include "GameTime.h"
#include "EffectManager.h"

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

	_update = &SushiMon::AliveUpdate;

	_animFrame = 0;
}


SushiMon::~SushiMon()
{
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

	DistanceAttenuation();

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
SushiMon::DamageUpdate()
{

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