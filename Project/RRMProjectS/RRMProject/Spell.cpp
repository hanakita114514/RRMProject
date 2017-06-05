#include "Spell.h"
#include "BulletManager.h"
#include "SinBullet.h"

Spell::Spell()
{
	Circle c = {};
	_circle = c;
	_circle.radius = 32;
}


Spell::~Spell()
{
}

void
Spell::TestSpell(Vector2 vec,Vector2 pos,Object *owner)
{
	const float DefaultAngle = 60;

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
				//dynamic_cast<SinBullet*>(bullet)->Return(true);
			}
		}
	}
}

void Spell::CircleShot(Vector2 vec, Vector2 pos, Object *owner)
{
	const float RAD = 3.141592 / 180;

	_pos = pos;
	_vec = vec;
	Bullet* bullet = nullptr;
	BulletManager& bm = BulletManager::Instance();
	int cnt = 0;

	Circle _circle = {};

	_circle.center = _pos;
	_circle.radius = 32;

	Vector2 circlePos = _pos;
	circlePos.y -= _circle.radius;

	Vector2 distance;

	for (int i = 0; i < 36; i++)
	{
		distance = circlePos - _circle.pos;
		circlePos.x += cos((10 * i) * RAD) * 10;
		circlePos.y += sin((10 * i) * RAD) * 10;

		bullet = bm.Create(BulletType::normal, _vec, ObjectType::enemy, Vector2(0, 0), owner);
		bullet->SetPos(circlePos);
	}
}
