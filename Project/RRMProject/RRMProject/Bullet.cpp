#include "Bullet.h"
#include <DxLib.h>


Bullet::Bullet()
{
	_circle.radius = BULLET_RADIUS;
}

Bullet::~Bullet()
{
}

void Bullet::Initialize(Vector2 vec, ObjectType type)
{

}

BulletType
Bullet::GetID()
{
	return _id;
}

bool 
Bullet::IsAlive()
{
	return _isAlive;
}

ObjectType
Bullet::GetObjType()
{
	return _objType;
}

void Bullet::Hit(Player* other)
{
	Destory();
}

void Bullet::Hit(Enemy* other)
{
	Destory();
}

void Bullet::Hit(Block* other)
{
	Destory();
}

Object*
Bullet::GetOwner()
{
	return _owner;
}

void 
Bullet::SetOwner(Object* obj)
{
	_owner = obj;
}