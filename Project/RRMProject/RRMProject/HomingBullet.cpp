#include "HomingBullet.h"
#include <math.h>
#include <DxLib.h>
#include "GameTime.h"


const float REDUCE_LIFE = 1.0f;

HomingBullet::HomingBullet(int handle,Vector2 vec)
{
	_handle = handle;
	_id = BulletType::homing;
	_life = 300.0f;
	_vel = vec;
	_vel.x *= 5;
	_homCnt = 0;
}


HomingBullet::~HomingBullet()
{

}

void
HomingBullet::Initialize(Vector2 vec,ObjectType type)
{
	_life = 300.0f;
	_objType = type;
	_isAlive = true;
	_vel = vec;
	_vel.x *= 3;
}

void
HomingBullet::Update()
{
	_homCnt++;

	LifeDecree();
	Move();
}

void
HomingBullet::Draw()
{
	DrawGraph(_circle.pos.x, _circle.pos.y, _handle, true);
}

void 
HomingBullet::SetAngle(Vector2* target, Vector2* own)
{
	_targetPos = target;
	_ownPos = own;

	Vector2 vec = *_targetPos - *_ownPos;
	
	float normal = sqrt(vec.x * vec.x + vec.y * vec.y);

	_vel = Vector2(vec.x / normal, vec.y / normal);
}

void HomingBullet::Move()
{
	if (_homCnt % 180 == 0)
	{
		Vector2 vec = *_targetPos - _circle.pos;
		float normal = sqrt(vec.x * vec.x + vec.y * vec.y);

		_vel = Vector2(vec.x / normal, vec.y / normal);
	}

	_circle.pos.x = (_circle.pos.x + (_vel.x)) * GameTime::Instance().GetTimeScale();
	_circle.pos.y = (_circle.pos.y + (_vel.y)) * GameTime::Instance().GetTimeScale();
}

void HomingBullet::LifeDecree()
{
	_life -= REDUCE_LIFE * GameTime::Instance().GetTimeScale();

	if (_life == 0)
	{
		_isAlive = false;
	}
}
