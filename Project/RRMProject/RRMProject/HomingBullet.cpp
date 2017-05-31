#include "HomingBullet.h"
#include <math.h>
#include <DxLib.h>
#include "GameTime.h"
#include "EnemyManager.h"


const float REDUCE_LIFE = 1.0f;

HomingBullet::HomingBullet(int handle,Vector2 vec)
{
	_handle = handle;
	_id = BulletType::homing;
	_life = 300.0f;
	_vel = vec;
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

}

bool 
HomingBullet::TargetSearch()
{
	//所有者がプレイヤーの場合 最も近くの敵を探す
	if (_owner->GetObjType() == ObjectType::player)
	{
		if (EnemyManager::Instance().GetEnemyList().size() == 0)
		{
			return false;
		}
		Enemy* nearEnemy = EnemyManager::Instance().GetEnemyList()[0];

		for (auto& e : EnemyManager::Instance().GetEnemyList())
		{
			if (e->IsDelete())
			{
				continue;
			}
			Position prevPos;
			prevPos.x = abs(nearEnemy->GetPosition().x - _owner->GetPosition().x);
			prevPos.y = abs(nearEnemy->GetPosition().y - _owner->GetPosition().y);

			Position newPos;
			newPos.x = abs(e->GetPosition().x - _owner->GetPosition().x);
			newPos.y = abs(e->GetPosition().y - _owner->GetPosition().y);

			if (newPos.x + newPos.y > prevPos.x + prevPos.y)
			{
				nearEnemy = e;
			}
		}

		_target = nearEnemy;

		return true;
	}
	//プレイヤー以外が撃った場合はプレイヤーを狙う
	else
	{
		//_targetPos.reset();
		return true;
	}

	return false;
}

void
HomingBullet::Update()
{
	_homCnt++;

	LifeDecrease();
	Move();
}

void
HomingBullet::Draw(const Vector2& offset)
{
	DrawGraph(_circle.pos.x, _circle.pos.y, _handle, true);
}

void HomingBullet::Move()
{
	if (_homCnt % 30 == 0)
	{
		if (TargetSearch())
		{
			Vector2 vec = _target->GetPosition() - _circle.pos;
			float normal = sqrt(vec.x * vec.x + vec.y * vec.y);

			//_vel = Vector2(vec.x / normal, vec.y / normal);

			_vel.x += vec.x / normal;
			_vel.y += vec.y / normal;
		}
	}

	_circle.pos.x = (_circle.pos.x + (_vel.x)) * GameTime::Instance().GetTimeScale();
	_circle.pos.y = (_circle.pos.y + (_vel.y)) * GameTime::Instance().GetTimeScale();
}

void HomingBullet::LifeDecrease()
{
	_life -= REDUCE_LIFE * GameTime::Instance().GetTimeScale();

	if (_life == 0)
	{
		_isAlive = false;
	}
}
