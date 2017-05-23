#include "NormalBullet.h"
#include "DxLib.h"

const float BULLET_SPEED = 5;

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
	_life = 10;
	_objType = type;
	_isAlive = true;
	_vel = vec;
	_vel.x *= 5;
	_freamCnt = 0;
}

void NormalBullet::Update()
{
	//CtlPointSet(_etyPoint, _endPoint, _vel);
	_freamCnt++;
	if (_freamCnt % 10 == 0)
	{
		_life--;
	}

	if (_life == 0 || _circle.pos.x < 0)
	{
		_isAlive = false;
	}

	_circle.pos = _circle.pos + _vel;
}

void NormalBullet::Draw()
{
	DxLib::DrawGraph(_circle.pos.x, _circle.pos.y, _handle, true);
}

