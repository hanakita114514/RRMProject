#include "NormalBullet.h"
#include "RRMLib.h"
#include "GameTime.h"

const float BULLET_SPEED = 5.0f;
const float REDUCE_LIFE = 1.0f;

NormalBullet::NormalBullet(int handle)
{
	_handle = handle;
	_id = BulletType::normal;
}

NormalBullet::~NormalBullet()
{
}

void NormalBullet::Initialize(Vector2 vec,ObjectType type)
{
	_life = 1000.0f;
	_objType = type;
	_isAlive = true;
	_vel = vec;
	_vel.x *= 5;
	_freamCnt = 0;
	_pow = 1.0f;
}

void NormalBullet::Update()
{
	//CtlPointSet(_etyPoint, _endPoint, _vel);



	if (_life <= 0.0f || _circle.pos.x < 0)
	{
		_isAlive = false;
	}

	if (_bs != BulletState::stop)
	{
		_life -= REDUCE_LIFE * GameTime::Instance().GetTimeScale(_owner);
		_circle.pos.x += _vel.x * GameTime::Instance().GetTimeScale(_owner);
		_circle.pos.y += _vel.y * GameTime::Instance().GetTimeScale(_owner);
	}
}

void NormalBullet::Draw(const Vector2& offset)
{
	_circle.DrawGraph(_handle);
}

