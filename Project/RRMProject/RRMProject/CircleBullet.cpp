#include "CircleBullet.h"
#include "DxLib.h"
#include "GameTime.h"

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
}

void
CircleBullet::Update()
{
	_life -= REDUCE_LIFE * GameTime::Instance().GetTimeScale();

	if (_life == 0)
	{
		_isAlive = false;
	}
	Move();
}

void
CircleBullet::Draw(const Vector2& offset)
{
	_circle.DrawGraph(_handle);
}

void
CircleBullet::Move()
{
	_circle.pos += _vel * GameTime::Instance().GetTimeScale();
}