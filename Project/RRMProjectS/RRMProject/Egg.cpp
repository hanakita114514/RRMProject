#include "Egg.h"
#include <DxLib.h>
#include "GameMain.h"
#include "MapManager.h"
#include <math.h>
#include "EffectManager.h"
#include "Mathematics.h"

const float GRAVITY = 0.75f;

Egg::Egg(int* handle, const Position& pos)
{
	for (int i = 0; i < 3; i++)
	{
		_img[i] = handle[i];
	}

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
	_circle.center = _rc.Center();

	_freamCnt++;
	_shotPos = Vector2(_rc.Left(), _rc.Top());

	if (_hitGround == true)
	{
		_vel.y = 0;
		_animCnt++;
		_junpCnt++;
		_shotCnt++;
	}
	else
	{
		_vel.y += GRAVITY;
	}

	if (CheckHitKey(KEY_INPUT_LEFT))
	{
		_vel.x = -2;
	}
	else if (CheckHitKey(KEY_INPUT_RIGHT))
	{
		_vel.x = 2;
	}


	(this->*_state)();

	Move();

	_vel.x = 0;

	if (_hp.GetHitPoint() <= 0)
	{
		_update = &Egg::DyingUpdate;
		EffectManager::Instance().Create(EffectType::erasure, _rc.Center(), Vector2(1.5f, 1.5f), 1.3f);
		_isAlive = false;
	}
}

void 
Egg::DyingUpdate()
{

}

void Egg::Update()
{
	(this->*_update)();
}

void Egg::Draw(const Vector2& offset)
{
	if (_update == &Egg::AliveUpdate)
	{
		Vector2 drawPos;
		drawPos.x = _rc.pos.x - offset.x;
		drawPos.y = _rc.pos.y - offset.y;

		_hpbar.Draw(Position(drawPos.x + 16, drawPos.y - 16), _hp);
		DxLib::DrawGraph((int)drawPos.x, (int)drawPos.y, _img[0], true);
	}
}

void Egg::Anim()
{
}

void Egg::Move()
{
	_rc.pos += _vel;
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
		Spell* spell = _absSpell->GetSpell(SpellType::CircleShot);
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
		_shotPos.x = _circle.center.x - (_circle.radius * 2) * cos(RAD * (cnt * 90) + _freamCnt) / 2;
		_shotPos.y = _circle.center.y - (_circle.radius * 2) * sin(RAD * (cnt * 90) + _freamCnt) / 2;
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
	Vector2 vec = shootPos - _circle.center;
	float normal = sqrt(vec.x * vec.x + vec.y * vec.y);
	
	_shootVec = Vector2(vec.x / normal, vec.y / normal);
}

void 
Egg::Weakening()
{

}