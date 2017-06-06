#include "Spell.h"
#include "BulletManager.h"
#include "SinBullet.h"
#include "Bullet.h"

Spell::Spell()
{
	Circle c = {};
	_circle = c;
	_circle.radius = 32;
	_freamCnt = 0;
	prevBullet = nullptr;
}


Spell::~Spell()
{
}

void
Spell::TestSpell(Vector2 vec,Vector2 pos,Object *owner)
{
	const float DefaultAngle = 60;
	_freamCnt++;

	if ((int)_freamCnt % 30 == 0)
	{
		_pos = pos;
		_vec = vec;
		Bullet* bullet = nullptr;
		BulletManager& bm = BulletManager::Instance();

		for (int j = 5; j > 0; --j)
		{
			bullet = bm.Create(BulletType::normal, _vec, ObjectType::enemy, Vector2(0, 0), owner);
			bullet->SetPos(_pos);

			for (int i = 0; i < 2; i++)
			{
				bullet = bm.Create(BulletType::sinBullet, _vec, ObjectType::enemy, Vector2(0, 0), owner);
				bullet->SetPos(_pos);
				if (i == 1)
				{
					dynamic_cast<SinBullet*>(bullet)->Return(true);
				}
			}
		}
	}
}

void Spell::CircleShot(Vector2 vec, Vector2 pos, Object *owner)
{
	const float RAD = 3.141592 / 180;

	_freamCnt++;

	if ((int)_freamCnt % 30 == 0)
	{
		_pos = pos;
		_vec = vec;
		Bullet* bullet = nullptr;
		BulletManager& bm = BulletManager::Instance();
		int cnt = 0;

		Circle _circle = {};

		_circle.center = _pos;
		_circle.radius = 32;

		Vector2 circlePos = _pos;
		circlePos.x -= _circle.radius;


		for (int i = 0; i < 6; i++)
		{
			circlePos.x += cos((60 * i) * RAD) * _circle.radius;
			circlePos.y += sin((60 * i) * RAD) * _circle.radius;

			bullet = bm.Create(BulletType::normal, _vec, ObjectType::enemy, Vector2(0,0), owner);
			bullet->SetPos(circlePos);
		}
	}
}

void
Spell::Comet(Vector2 vec, Vector2 pos, Object *owner)
{
	const float PI = 3.141592;
	const float RAD = PI / 180;
	const int BULLET_MAX = 12;
	int bCnt = 0;

	_freamCnt++;

	if ((int)_freamCnt % 30 == 0)
	{
		_pos = pos;
		_vec = vec;
		Bullet* bullet = nullptr;
		BulletManager& bm = BulletManager::Instance();
		int cnt = 0;

		Circle _circle = {};

	/*	for (int i = 0; i < 3; i++)
		{
			_circle.center.x = _pos.x + i * 30;
			_circle.center.y = _pos.y - i * 50;
			_circle.radius = 16;

			_circle.pos = _circle.center;
			_circle.pos.y = _circle.center.y - _circle.radius;

			_vec.x = cos(60 * RAD)* -2;
			_vec.y = 5;

			for (int i = 0; i < 12; i++)
			{
				_circle.pos.x += cos((30 * i) * RAD) * _circle.radius;
				_circle.pos.y += sin((30 * i) * RAD) * _circle.radius;

				bullet = bm.Create(BulletType::normal, _vec, ObjectType::enemy, Vector2(0, 0), owner);
				bullet->SetPos(_circle.pos);
				bullet->Stop();
			}
		}*/

		for (int i = 0; i < 12; i++)
		{
			_circle.center.x = _pos.x;
			_circle.center.y = _pos.y;
			_circle.radius = 16;

			_circle.pos = _circle.center;
			_circle.pos.y = _circle.center.y - _circle.radius;

			_vec.x = cos(60 * RAD)* -2;
			_vec.y = 5;

			_circle.pos.x += cos((30 * bCnt) * RAD) * _circle.radius;
			_circle.pos.y += sin((30 * bCnt) * RAD) * _circle.radius;

			bullet = bm.Create(BulletType::normal, _vec, ObjectType::enemy, Vector2(0, 0), owner);
			bullet->SetPos(_circle.pos);
			bullet->Stop();
			prevBullet = bullet;
			bCnt++;
		}
	}
	if ((int)_freamCnt % 40 == 0)
	{
		prevBullet->Move();
	}
}
