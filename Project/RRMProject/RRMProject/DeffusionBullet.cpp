#include "DeffusionBullet.h"
#include <DxLib.h>
#include <math.h>
#include <time.h>

const int BULLET_SPEED = 5;

DeffusionBullet::DeffusionBullet(int handle)
{
	_handle = handle;
	_id = BulletType::deffusion;
}


DeffusionBullet::~DeffusionBullet()
{
}

void
DeffusionBullet::Initialize(Vector2 vec, ObjectType type)
{
	_vec = vec;
	_objType = type;
	_isAlive = true;
	_freamCnt = 0;
	_life = 10;

	_vel = _vec * BULLET_SPEED;

	Deffusion();
}

void
DeffusionBullet::Update()
{
	_freamCnt++;

	if (_freamCnt % 10 == 0)
	{
		_life--;
		if (_life <= 0)
		{
			_isAlive = false;
		}
	}
	Move();
}

void
DeffusionBullet::Draw()
{
	DxLib::DrawGraph(_circle.pos.x, _circle.pos.y, _handle, true);
}

void
DeffusionBullet::Move()
{
	_circle.pos += _vel;
}

void
DeffusionBullet::Deffusion()
{
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> rand(-30, 30);

	_randVec.y = rand(mt);
	std::uniform_int_distribution<> xrand(0, 30);
	_randVec.x = xrand(mt);

	_randVec += _circle.pos;
	_vel = Normalize(_randVec,_circle.pos);

	_vel = _vel * BULLET_SPEED ;
	_vel.x *= _vec.x;
}


