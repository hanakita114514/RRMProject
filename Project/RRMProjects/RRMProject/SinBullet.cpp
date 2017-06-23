#include "SinBullet.h"
#include <math.h>
#include <RRMLib.h>
#include "GameTime.h"
#include "Mathematics.h"

const int AMPLITUDE = 1;			//êUÇÍïù
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
	_vel.x *= 5;
	_life = 100.0f;
	_freamCnt = 0;
	_id = BulletType::sinBullet;
	_objType = type;
	_returnFlag = false;
}

void 
SinBullet::Update()
{
	_freamCnt++;

	_vel.y = sin((RAD * _freamCnt)) * AMPLITUDE;

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
	if (_returnFlag)
	{
		_vel.y *= -1;

	}

	_circle.pos.x += _vel.x * GameTime::Instance().GetTimeScale(_owner);
	_circle.pos.y += _vel.y * GameTime::Instance().GetTimeScale(_owner);

	if (_circle.pos.x < 0 || _circle.pos.x > 1280)
	{
		_isAlive = false;
	}
}

void 
SinBullet::LifeDecrease()
{
	_life -= REDUCE_LIFE * GameTime::Instance().GetTimeScale(_owner);

	if (_life < 0)
	{
		_isAlive = false;
	}
}



