#include "DropBullet.h"

const float BulletSpeed = 5.0f;
const float GravityScale = 0.75f;

DropBullet::DropBullet()
{

}

DropBullet::DropBullet(int handle)
{
	_handle = handle;
}


DropBullet::~DropBullet()
{

}

void 
DropBullet::Initialize(const Position& pos, Vector2 vec, ObjectType type)
{
	_objType = type;
	_circle.pos = pos;
	_vel = vec * BulletSpeed;
}

void
DropBullet::Update()
{
	_vel.y = GravityScale;
	_circle.pos += _vel;
}

void
DropBullet::Draw(const Vector2& offset)
{
	Circle c = _circle;
	c.pos -= offset;
	c.DrawGraph(_handle);
}