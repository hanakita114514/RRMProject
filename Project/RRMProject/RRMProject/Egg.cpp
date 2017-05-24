#include "Egg.h"
#include <DxLib.h>
#include "GameMain.h"
#include "MapManeger.h"
#include <math.h>

const float GRAVITY = 0.75f;
const float RAD = 3.141592 / 180;

Egg::Egg(int* handle)
{
	for (int i = 0; i < 3; i++)
	{
		_img[i] = handle[i];
	}
	_animCnt = 0;
	_shotCnt = 0;

	_state = &Egg::Wait;
	_freamCnt = 0;

	Rect r = {};
	_rc = r;
	_rc.w = 64;
	_rc.h = 64;
	_rc.pos = Vector2(640, 0);
	_junpCnt = 0;
	_vel = Vector2(0, 0);
	_dir = Vector2(-1, 0);

	Circle c = {};
	_circle = c;
	_circle.radius = _rc.w / 2;
}

Egg::~Egg()
{
}

void Egg::Initialize()
{

}

void Egg::Update()
{
	_bMng = GameMain::Instance().GetBulletMng();
	_circle.center = _rc.Center();
		
	_freamCnt++;

	for (int i = 0; i < ShootDir::MAX; i++)
	{
		_shootPos[i].x = _circle.center.x - (_circle.radius * 2) * cos(RAD * (_freamCnt + i * 90)) / 2;
		_shootPos[i].y = _circle.center.y - (_circle.radius * 2) * sin(RAD * (_freamCnt + i * 90)) / 2;
	}

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


	(this->*_state)();

	//Jump();
	Move();
}

void Egg::Draw()
{
	DxLib::DrawGraph(_rc.pos.x,_rc.pos.y, _img[0], true);
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
		Shot(BulletType::circleBullet,4);
		_state = &Egg::Wait;
}

void Egg::Jump()
{
	if ((_junpCnt % 60 == 0 && _junpCnt != 0) && _hitGround)
	{
		_vel.y = -10;
		_hitGround = false;
		_junpCnt++;
	}
}

void Egg::Wait()
{

	if ((_shotCnt % 10 == 0 && _shotCnt != 0))
	{
		_state = &Egg::Shot;
	}

}

void Egg::Shot(BulletType type, int count)	//UŒ‚
{
	Bullet* bullet = nullptr;
	BulletFactory* fac = _bMng->GetFactory();
	int cnt = count;

	switch (type)
	{
	case BulletType::normal:
	{
		bullet = fac->GetBullet(type, _dir, ObjectType::enemy);
		bullet->SetPos(_rc.pos);
	}
	case BulletType::homing:
	{
		bullet = fac->GetBullet(type, _dir, ObjectType::enemy);
		bullet->SetPos(_rc.pos);
		break;
	}
	case BulletType::sinBullet:
	{
		bullet = fac->GetBullet(type,_dir, ObjectType::enemy);
		bullet->SetPos(_rc.pos);
		break;
	}
	case BulletType::deffusion:
	{
			bullet = fac->GetBullet(type, _dir, ObjectType::enemy);
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
		bullet = fac->GetBullet(type, _dir, ObjectType::enemy, _rc.pos);
		bullet->SetPos(_rc.pos);
		break;
	}
	case BulletType::circleBullet:
	{
		if (cnt < ShootDir::UP)
		{
			break;
		}
		--cnt;
		ShotAngleCalc(_shootPos[cnt]);
		bullet = fac->GetBullet(type, _shootVec, ObjectType::enemy);
		bullet->SetPos(_shootPos[cnt]);
		if (cnt != 0)
		{
			Shot(type, cnt);
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

void Egg::Hit(Player* other)
{

}
void Egg::Hit(Block* other)
{
	_rc.SetBottom(other->GetRect().Top());
	_hitGround = true;
}
