#include "Enemy.h"
#include "Block.h"
#include "Bullet.h"
#include "Player.h"
#include <math.h>
#include "GameTime.h"

static const double GRAVITY = 0.75f;

Enemy::Enemy() : _hp(50.0f), _friction(0.2)
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
		_vel.x *= -1;
		_dir.x *= -1;
	}
	if (_rc.Right() > camera.GetCameraRect().rpos.x)
	{
		_rc.pos.x = camera.GetCameraRect().rpos.x - _rc.w;
		_vel.x *= -1;
		_dir.x *= -1;
	}
	if (_rc.Top() > camera.GetMapSize().pos.y + camera.GetMapSize().h)
	{
		Destory();
	}
}

void 
Enemy::Gravity()
{
	_vel.y += GRAVITY * GameTime::Instance().GetTimeScale(this);

	if (_hitGround)
	{
		_vel.y = 0;
	}
}

void
Enemy::Hit(Block* other)
{
	//_rc.SetBottom(other->GetRect().Top());
	//_hitGround = true;
	//_vel.y = 0;

	float lenX = fabs(_rc.pos.x - other->GetRect().pos.x);
	float lenY = fabs(_rc.pos.y - other->GetRect().pos.y);

	if (lenX < lenY) // Y軸に押し戻す
	{
		if (_vel.y > 0)		//落下している場合
		{
			if (_rc.pos.y < other->GetRect().pos.y && !_hitGround)
			{
				_rc.SetBottom(other->GetRect().Top());
				_hitGround = true;
				_vel.y = 0;
			}
		}
		else				//飛んでいる場合
		{
			if (_rc.pos.y > other->GetRect().pos.y)
			{
				_rc.SetTop(other->GetRect().Bottom());
				_vel.y = 0;
			}
		}
	}

	if (lenY < lenX)	//X軸に押し戻す
	{
		if (_dir.x == 1)		//右移動
		{
			if (_rc.pos.x < other->GetRect().pos.x)
			{
				_rc.SetRight(other->GetRect().Left());
				_vel.x *= -1;
				_dir.x *= -1;
			}
		}
		else				//左移動
		{
			if (_rc.pos.x > other->GetRect().pos.x)
			{
				_rc.SetLeft(other->GetRect().Right());
				_vel.x *= -1;
				_dir.x *= -1;
			}
		}
	}
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
		_vel.x -= _friction;
	}
	if (_vel.x < 0)
	{
		_vel.x += _friction;
	}
	if (abs(_vel.x) < 0.5f)
	{
		_vel.x = 0;
	}
}

void 
Enemy::Destory()
{
	_isAlive = false;
}

EnemyType 
Enemy::GetEnemyType()
{
	return EnemyType::none;
}