#include "CircleBullet.h"
#include "RRMLib.h"
#include "GameTime.h"
#include <math.h>

const float REDUCE_LIFE = 1.0f;

CircleBullet::CircleBullet(int handle)
{
	_handle = handle;
	_id = BulletType::circleBullet;
}


CircleBullet::~CircleBullet()
{
}

void
CircleBullet::Initialize(Vector2 vec, ObjectType type)
{
	_life = 100.0f;
	_vel = vec * 5;
	_objType = type;
	_isAlive = true;
	stopFlag = false;
	_fream = 0;

	_bs = BulletState::move;

}

void
CircleBullet::Update()
{
	if (_bs != BulletState::stop)
	{
		_life -= REDUCE_LIFE * GameTime::Instance().GetTimeScale();
		_circle.pos += _vel * GameTime::Instance().GetTimeScale();
	}
	if (_life < 0)
	{
		_isAlive = false;
	}
	_fream++;
	if (_fream == 60)
	{
		_bs = BulletState::move;
	}
}

void
CircleBullet::Draw(const Vector2& offset)
{
	_circle.DrawGraph(_handle);
}
