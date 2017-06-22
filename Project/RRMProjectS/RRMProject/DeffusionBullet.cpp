#include "DeffusionBullet.h"
#include <RRMLib.h>
#include <math.h>
#include <time.h>
#include "GameTime.h"

const float BULLET_SPEED = 5.0f;
const float REDUCE_LIFE = 1.0f;

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
	_life = 100.0f;

	_vel = _vec * BULLET_SPEED;

	Deffusion();
}

void
DeffusionBullet::Update()
{

	_life -= REDUCE_LIFE * GameTime::Instance().GetTimeScale(_owner);

	if (_life <= 0)
	{
		_isAlive = false;
	}
	Move();
}

void
DeffusionBullet::Draw(const Vector2& offset)
{
	_circle.DrawGraph(_handle);
}

void
DeffusionBullet::Move()
{
	_circle.pos += _vel * GameTime::Instance().GetTimeScale(_owner);
}

void
DeffusionBullet::Deffusion()
{
	std::random_device rnd;
	std::mt19937 mt(rnd());
	std::uniform_int_distribution<> rand(-30, 30);

	_randVec.y = (float)rand(mt);
	std::uniform_int_distribution<> xrand(0, 30);
	_randVec.x = (float)xrand(mt);

	_randVec += _circle.pos;
	_vel = Normalize(_randVec,_circle.pos);

	_vel = _vel * BULLET_SPEED ;
	_vel.x *= _vec.x;
}


