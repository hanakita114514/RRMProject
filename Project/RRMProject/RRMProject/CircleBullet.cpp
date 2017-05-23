#include "CircleBullet.h"
#include "DxLib.h"
#include "GameTime.h"

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
	_lifeCnt = 0;
	_isAlive = true;
}

void
CircleBullet::Update()
{

	_life -= 1 * GameTime::Instance().GetTimeScale();
	if (_life == 0)
	{
		_isAlive = false;
	}
	Move();
}

void
CircleBullet::Draw()
{
	DxLib::DrawGraph(_circle.pos.x, _circle.pos.y, _handle, true);
}

void
CircleBullet::Move()
{
	_circle.pos += _vel * GameTime::Instance().GetTimeScale();
}