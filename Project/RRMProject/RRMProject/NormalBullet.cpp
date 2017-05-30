#include "NormalBullet.h"
#include "DxLib.h"
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
	_life = 100.0f;
	_objType = type;
	_isAlive = true;
	_vel = vec;
	_vel.x *= 5;
	_freamCnt = 0;
}

void NormalBullet::Update()
{
	//CtlPointSet(_etyPoint, _endPoint, _vel);

	_life -= REDUCE_LIFE * GameTime::Instance().GetTimeScale();


	if (_life == 0 || _circle.pos.x < 0)
	{
		_isAlive = false;
	}

	_circle.pos.x += _vel.x * GameTime::Instance().GetTimeScale();
	_circle.pos.y += _vel.y * GameTime::Instance().GetTimeScale();
}

void NormalBullet::Draw(const Vector2& offset)
{
	DxLib::DrawGraph(_circle.pos.x, _circle.pos.y, _handle, true);
}

