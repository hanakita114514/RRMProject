#include "Egg.h"
#include <RRMLib.h>
#include "GameMain.h"
#include "MapManager.h"
#include "EffectManager.h"
#include "Mathematics.h"
#include <math.h>
#include "GameTime.h"

const float ANIM_SIZE_X = 64.0f;
const float ANIM_SIZE_Y = 64.0f;

const int IMAGE_NUM = 3;

Egg::Egg(int handle, const Position& pos)
{
	_handle = handle;

	_animCnt = 0;
	_shotCnt = 0;

	_state = &Egg::Wait;
	_update = &Egg::AliveUpdate;
	_freamCnt = 0;

	Rect r = {};
	_rc = r;
	_rc.w = 64;
	_rc.h = 64;
	_rc.pos = pos;
	_junpCnt = 0;
	_vel = Vector2(0, 0);
	_dir = Vector2(-1, 0);

	Circle c = {};
	_circle = c;
	_circle.radius = _rc.w / 2;

	_isAlive = true;

}

Egg::~Egg()
{
	BulletManager::Instance().Delete(this);
}

void Egg::Initialize()
{

}

void 
Egg::AliveUpdate()
{
	_circle.pos = _rc.Center();

	_freamCnt++;
	_shotPos = Vector2(_rc.Left(), _rc.Top());

	if (_hitGround)
	{
		_vel.y = 0;
		_animCnt += GameTime::Instance().GetTimeScale(this);
		_junpCnt++;
		_shotCnt++;
	}
	Gravity();

	(this->*_state)();

	Move();
	Anim();
	_hpbar.Commit();

	if (_hp.GetHitPoint() <= 0)
	{
		_update = &Egg::DyingUpdate;
		EffectManager::Instance().Create(EffectType::erasure, _rc.Center(), Vector2(1.5f, 1.5f), 1.3f);
		_isAlive = false;
	}

	if (_isDamage)
	{
		_update = &Egg::DamageUpdate;
	}
}

void 
Egg::DamageUpdate()
{
	DistanceAttenuation();

	if (_hitGround)
	{
		_vel.y = 0;
		_animCnt += GameTime::Instance().GetTimeScale(this);
		_junpCnt++;
		_shotCnt++;
	}

	Gravity();

	_rc.pos += _vel;

	if (_vel.x == 0)
	{
		_isDamage = false;
		_update = &Egg::AliveUpdate;
		_hpbar.Commit();
	}
}

void 
Egg::DyingUpdate()
{

}

void Egg::Update()
{
	if (!_hitStop.IsHitStop())
	{
		(this->*_update)();
	}
	_hpbar.Update();
	_hitStop.Update();
}

void Egg::Draw(const Vector2& offset)
{
	if (_update != &Egg::DyingUpdate)
	{
		Vector2 drawPos;
		drawPos.x = _rc.pos.x - offset.x;
		drawPos.y = _rc.pos.y - offset.y;

		_hpbar.Draw(Position(drawPos.x + _rc.w / 4, drawPos.y - _rc.h / 4), _hp);
		//RRMLib::DrawGraph((int)drawPos.x, (int)drawPos.y, _handle);
		RRMLib::DrawRectGraph(drawPos.x, drawPos.y, _uv.x, _uv.y, ANIM_SIZE_X, ANIM_SIZE_Y, _handle, true, false);
	}
}

void Egg::Anim()
{
	static const Vector2 animUV[] =
	{
		Vector2(ANIM_SIZE_X * 0, 0),
		Vector2(ANIM_SIZE_X * 1, 0),
		Vector2(ANIM_SIZE_X * 2, 0),
		Vector2(ANIM_SIZE_X * 3, 0),
	};

	int animFrame = (int)_animCnt * 0.2f;

	_uv = animUV[animFrame % IMAGE_NUM];
}

void Egg::Move()
{
	_rc.pos += _vel * GameTime::Instance().GetTimeScale(this);
}

void Egg::Shot()
{
		Shot(BulletType::circleBullet,1);
		_state = &Egg::Wait;
}

void Egg::Jump()
{
	if ((_junpCnt % 30 == 0 && _junpCnt != 0) && _hitGround)
	{
		_vel.y = -10;
		_hitGround = false;
		_junpCnt++;
	}
}

void Egg::Wait()
{
	if (_hitGround)
	{
		Spell* spell = _absSpell->GetSpell(SpellType::Comet);
		spell->Create(Vector2(-1, 0), _rc.pos, this);
	}

	int i = 0;
}

void Egg::Shot(BulletType type, int count)	//UŒ‚
{
	Bullet* bullet = nullptr;
	BulletManager& bm = BulletManager::Instance();
	int cnt = count;

	switch (type)
	{
	case BulletType::normal:
	{
		bullet = bm.Create(type, _dir, ObjectType::enemy, _rc.pos, this);
		bullet->SetPos(_rc.pos);
	}
	case BulletType::homing:
	{
		bullet = bm.Create(type, _dir, ObjectType::enemy, _rc.pos, this);
		bullet->SetPos(_rc.pos);
		break;
	}
	case BulletType::sinBullet:
	{
		bullet = bm.Create(type, _dir, ObjectType::enemy, _rc.pos, this);
		bullet->SetPos(_rc.pos);
		break;
	}
	case BulletType::deffusion:
	{
			bullet = bm.Create(type, _dir, ObjectType::enemy, _rc.pos, this);
			bullet->SetPos(_rc.pos);
			if (cnt != 0)
			{
				//ƒJƒEƒ“ƒg‚ª‚È‚­‚È‚é‚Ü‚Å’e‚ð¶¬‚·‚é
				Shot(type, --cnt);
			}
			else
			{
				break;
			}
	}
	case BulletType::bezier:
	{
		bullet = bm.Create(type, _dir, ObjectType::enemy, _rc.pos, this);
		bullet->SetPos(_rc.pos);
		break;
	}
	case BulletType::circleBullet:
	{
		_shotPos.x = _circle.pos.x - (_circle.radius * 2) * cos(RAD * (cnt * 90) + _freamCnt) / 2;
		_shotPos.y = _circle.pos.y - (_circle.radius * 2) * sin(RAD * (cnt * 90) + _freamCnt) / 2;
		--cnt;

		ShotAngleCalc(_shotPos);
		bullet = bm.Create(type, _shootVec, ObjectType::enemy, _rc.pos, this);
		bullet->SetPos(_shotPos);

		if (cnt != 0)
		{
			Shot(type, cnt);
		}
		else
		{
			break;
		}
	}
	default:
		break;
	}
}

void Egg::ShotAngleCalc(Vector2 shootPos)
{
	Vector2 vec = shootPos - _circle.pos;
	float normal = sqrt(vec.x * vec.x + vec.y * vec.y);
	
	_shootVec = Vector2(vec.x / normal, vec.y / normal);
}

void 
Egg::Weakening()
{

}