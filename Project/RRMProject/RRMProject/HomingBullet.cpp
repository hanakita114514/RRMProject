#include "HomingBullet.h"
#include <math.h>
#include <DxLib.h>

HomingBullet::HomingBullet(int handle,Vector2 vec)
{
	_handle = handle;
	_id = BulletType::homing;
	_life = 10;
	_vel = vec;
	_vel.x *= 5;
	_lifeCnt = 0;
	_homCnt = 0;
}


HomingBullet::~HomingBullet()
{

}

void
HomingBullet::Initialize(Vector2 vec,ObjectType type)
{
	_life = 10;
	_objType = type;
	_isAlive = true;
	_vel = vec;
	_vel.x *= 3;
}

void
HomingBullet::Update()
{
	_lifeCnt++;
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
HomingBullet::SetAngle(Vector2* pPos, Vector2* ePos)
{
	_pPos = pPos;
	_ePos = ePos;

	Vector2 vec = *pPos - *ePos;
	
	float normal = sqrt(vec.x * vec.x + vec.y * vec.y);

	_vel = Vector2(vec.x / normal, vec.y / normal);
}

void HomingBullet::Move()
{
	if (_homCnt % 180 == 0)
	{
		Vector2 vec = *_pPos - _circle.pos;
		float normal = sqrt(vec.x * vec.x + vec.y * vec.y);

		_vel = Vector2(vec.x / normal, vec.y / normal);
	}

	_circle.pos.x = _circle.pos.x + (_vel.x);
	_circle.pos.y = _circle.pos.y + (_vel.y);
}

void HomingBullet::LifeDecree()
{
	if (_lifeCnt % 300 == 0)
	{
		_life--;
		if (_life == 0)
		{
			_isAlive = false;
		}
	}
}
