#include "SinBullet.h"
#include <math.h>
#include <DxLib.h>

const float RAD = 3.14 / 2;				//ÉâÉWÉAÉì
const float ANGLE = 30;				//î≠éÀäp
const int AMPLITUDE = 5;			//êUÇÍïù

SinBullet::SinBullet(int handle)
{
	_handle = handle;
	_vel.x = 1;
	_id = BulletType::sinBullet;
}


SinBullet::~SinBullet()
{

}

void
SinBullet::Initialize(Vector2 vec,ObjectType type)
{
	_isAlive = true;
	_vel = vec;
	_vel.x *= 6.5;
	_freamCnt = 0;
	_id = BulletType::sinBullet;
	_objType = type;
}

void 
SinBullet::Update()
{
	_freamCnt++;

	_vel.y = sin((RAD /ANGLE * _freamCnt) - 1) * AMPLITUDE;
	if (_isAlive == false)
	{
		int i = 0;
	}

	Move();
}

void
SinBullet::Draw()
{
	DxLib::DrawGraph(_circle.pos.x, _circle.pos.y, _handle, true);
}

void
SinBullet::Move()
{
	_circle.pos = _circle.pos + _vel;
	if (_circle.pos.x < 0 || _circle.pos.x > 1280)
	{
		_isAlive = false;
	}
}

void 
SinBullet::LifeDecree()
{

}



