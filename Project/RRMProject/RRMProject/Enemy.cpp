#include "Enemy.h"
#include "Block.h"


Enemy::Enemy()
{
}


Enemy::~Enemy()
{
}

void Enemy::Initialize()
{

}

ObjectType 
Enemy::GetObjType()
{
	return ObjectType::enemy;
}

void
Enemy::Hit(Block* other)
{
	_rc.SetBottom(other->GetRect().Top());
	_hitGround = true;
	_vel.y = 0;
}

void 
Enemy::Hit(Player* other)
{

}

void
Enemy::Hit(Bullet* other)
{

}