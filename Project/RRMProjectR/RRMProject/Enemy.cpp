#include "Enemy.h"
#include "Block.h"
#include "Bullet.h"
#include "Player.h"
#include <math.h>

Enemy::Enemy() : _hp(50.0f)
{
	_absSpell = new AbstractSpell();
	_hitGround = false;
	_isDamage = false;
}


Enemy::~Enemy()
{
	delete _absSpell;
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
Enemy::ScreenLimit(Camera& camera)
{
	if (_rc.pos.x < camera.GetCameraRect().lpos.x)
	{
		_rc.pos.x = camera.GetCameraRect().lpos.x;
	}
	if (_rc.Right() > camera.GetCameraRect().rpos.x)
	{
		_rc.pos.x = camera.GetCameraRect().rpos.x - _rc.w;
	}
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
	if (other->GetObjType() == ObjectType::player)
	{
		_hp.Damage((int)other->GetPower());
	}

}

void
Enemy::Damage(float power, const Vector2& vec)
{
	_hp.Damage(power);
	_vel = vec;
	_isDamage = true;
}

void 
Enemy::DistanceAttenuation()
{
	if (_vel.x > 0)
	{
		_vel.x -= 0.2f;
	}
	if (_vel.x < 0)
	{
		_vel.x += 0.2f;
	}
	if (abs(_vel.x) < 0.5f)
	{
		_vel.x = 0;
	}
}