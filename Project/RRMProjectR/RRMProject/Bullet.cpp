#include "Bullet.h"
#include <RRMLib.h>
#include "EffectManager.h"
#include "Player.h"
#include "GameTime.h"

Bullet::Bullet()
{
	_circle.radius = BULLET_RADIUS;
	_pow = 5.0f;
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
	if (!other->IsAvoidance())
	{
		Destory();
	}
}

void Bullet::Hit(Enemy* other)
{
	Destory();
}

void Bullet::Hit(Block* other)
{
	Destory();
}

void Bullet::Hit(Bullet* other)
{

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

void 
Bullet::Finalize()
{
	EffectManager::Instance().Create(EffectType::hit1 , _circle.pos, Vector2(0.3f, 0.3f), 0.5);
}