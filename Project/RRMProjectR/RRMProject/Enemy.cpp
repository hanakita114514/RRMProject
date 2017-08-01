#include "Enemy.h"
#include "Block.h"
#include "Bullet.h"
#include "Player.h"
#include <math.h>
#include "GameTime.h"

static const float GRAVITY = 0.75f;
static const float LIFE = 50.0f;
static const float FRICTION = 0.2f;
static const float ARMOR_LIFE = 50.0f;

Enemy::Enemy() : _hp(LIFE), _friction(FRICTION), _armor(ARMOR_LIFE)
{
	_absSpell = new AbstractSpell();
	_hitGround = false;
	_isDamage = false;
	_hitBox = nullptr;
	_isSearch = false;
	_animFrame = 0;
	_targetPos = Position(0, 0);
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
		HitStop(5);
		//camera.Quake(Vector2(5, 0));
	}
	if (_rc.Right() > camera.GetCameraRect().rpos.x)
	{
		_rc.pos.x = camera.GetCameraRect().rpos.x - _rc.w;
		_vel.x *= -1;
		_dir.x *= -1;
		HitStop(5);
		//camera.Quake(Vector2(5, 0));
	}
	if (_rc.Top() < camera.GetMapSize().pos.y - _rc.h)
	{
		_rc.pos.y = camera.GetMapSize().pos.y - _rc.h;
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
	float lenX = fabs(_rc.pos.x - other->GetRect().pos.x);
	float lenY = fabs(_rc.pos.y - other->GetRect().pos.y);

	if (lenX < lenY) // Yé≤Ç…âüÇµñﬂÇ∑
	{
		if (_vel.y > 0)		//óéâ∫ÇµÇƒÇ¢ÇÈèÍçá
		{
			if (_rc.pos.y < other->GetRect().pos.y && !_hitGround)
			{
				_rc.SetBottom(other->GetRect().Top());
				_hitGround = true;
				_vel.y = 0;
			}
		}
		else				//îÚÇÒÇ≈Ç¢ÇÈèÍçá
		{
			if (_rc.pos.y > other->GetRect().pos.y)
			{
				_rc.SetTop(other->GetRect().Bottom());
				_vel.y = 0;
			}
		}
	}

	if (lenY < lenX)	//Xé≤Ç…âüÇµñﬂÇ∑
	{
		if (_dir.x == 1)		//âEà⁄ìÆ
		{
			if (_rc.pos.x < other->GetRect().pos.x)
			{
				_rc.SetRight(other->GetRect().Left());
				_vel.x *= -1;
				_dir.x *= -1;
				if (_isDamage)
				{
					HitStop(5);
				}
			}
		}
		else				//ç∂à⁄ìÆ
		{
			if (_rc.pos.x > other->GetRect().pos.x)
			{
				_rc.SetLeft(other->GetRect().Right());
				_vel.x *= -1;
				_dir.x *= -1;
				if (_isDamage)
				{
					HitStop(5);
				}
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
		_hp.Damage(other->GetPower());
	}

}

void
Enemy::Damage(float power, const Vector2& vec)
{
	_hp.Damage(power);
	_armor.Damage(power);
	_vel += vec;
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

void
Enemy::SetFootHit(bool flag)
{
	_footCheck = flag;
}

void 
Enemy::SearchHit(const Position& targetPos)
{
	_isSearch = true;
	_targetPos = targetPos;
}

void
Enemy::SearchFailed()
{
	_isSearch = false;
}

void 
Enemy::ColDraw()
{
	if (_hitBox)
	{
		for (auto& f : _hitBox->GetFootRects())
		{
			f.DrawBox();
		}
		for (auto& s : _hitBox->GetSearchRects())
		{
			s.DrawBox();
		}
		for (auto& a : _hitBox->GetAttackBoxes())
		{
			a.rc.DrawBox();
		}
	}
}

void 
Enemy::SearchClear()
{
	_hitBox->SearchClear();
}
