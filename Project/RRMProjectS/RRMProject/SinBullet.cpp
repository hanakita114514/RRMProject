#include "SinBullet.h"
#include <math.h>
#include <DxLib.h>
#include "GameTime.h"

const float RAD = 3.14f / 2.0f;				//ÉâÉWÉAÉì
const float ANGLE = 30.0;				//î≠éÀäp
const int AMPLITUDE = 5;			//êUÇÍïù
const float REDUCE_LIFE = 1.0f;

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
	_life = 100.0f;
	_freamCnt = 0;
	_id = BulletType::sinBullet;
	_objType = type;
}

void 
SinBullet::Update()
{
	_freamCnt++;

	_vel.y = sin((RAD /ANGLE * _freamCnt) - 1) * AMPLITUDE;

	LifeDecrease();

	Move();
}

void
SinBullet::Draw(const Vector2& offset)
{
	_circle.DrawGraph(_handle);
}

void
SinBullet::Move()
{
	_circle.pos.x += _vel.x * GameTime::Instance().GetTimeScale();
	_circle.pos.y += _vel.y * GameTime::Instance().GetTimeScale();

	if (_circle.pos.x < 0 || _circle.pos.x > 1280)
	{
		_isAlive = false;
	}
}

void 
SinBullet::LifeDecrease()
{
	_life -= REDUCE_LIFE * GameTime::Instance().GetTimeScale();

	if (_life == 0)
	{
		_isAlive = true;
	}
}



