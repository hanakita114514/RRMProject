#include "CircleShot.h"
#include "BulletManager.h"


CircleShot::CircleShot()
{
}


CircleShot::~CircleShot()
{
}

void 
CircleShot::Create(Vector2 vec, Vector2 pos, Object *owner)
{
	const float RAD = 3.141592 / 180;

	_freamCnt++;

	if ((int)_freamCnt % 2 == 0)
	{

		_pos = pos;
		_vec = vec;
		Bullet* bullet = nullptr;
		BulletManager& bm = BulletManager::Instance();
		int cnt = 0;

		Circle _circle = {};

		_circle.center = _pos;
		_circle.radius = 64;

		Vector2 circlePos = _pos;
		circlePos.x -= _circle.radius;


		for (int i = 0; i < 6; i++)
		{
			circlePos.x += cos((60 * i) * RAD) * _circle.radius;
			circlePos.y += sin((60 * i) * RAD) * _circle.radius;

			bullet = bm.Create(BulletType::normal, _vec, ObjectType::enemy, Vector2(0, 0), owner);
			bullet->SetPos(circlePos);
		}
	}
}
