#include "Comet.h"
#include "BulletManager.h"
#include "Mathematics.h"

Comet::Comet()
{
}


Comet::~Comet()
{
}

void Comet::Create(Vector2 vec, Vector2 pos, Object *owner)
{
	const int BULLET_MAX = 12;

	_pos = pos;
	_vec = vec;

	Bullet* bullet = nullptr;
	BulletManager& bm = BulletManager::Instance();

	Circle _circle = {};

	if (bCnt != 12)
	{
		//Šî€‚Æ‚È‚é‰~‚Ì’†SÀ•W‚Æ”¼Œa‚ðÝ’è‚·‚é-----------------
		_circle.center.x = _pos.x;
		_circle.center.y = _pos.y;
		_circle.radius = 48;
		//-------------------------------------------------------

		//‰~‚ÌÀ•W‚ðÝ’è‚·‚é-------------------------------------
		_circle.pos = _circle.center;
		_circle.pos.y = _circle.center.y - _circle.radius;
		//-------------------------------------------------------

		_vec.x = cos(60 * RAD)* -2;
		_vec.y = 5;

		_circle.pos.x += cos((360 / BULLET_MAX) * (bCnt % BULLET_MAX) * RAD) * _circle.radius;
		_circle.pos.y += sin((360 / BULLET_MAX) * (bCnt % BULLET_MAX) * RAD) * _circle.radius;

		bullet = bm.Create(BulletType::normal, _vec, ObjectType::enemy, Vector2(0, 0), owner);
		bullet->SetPos(_circle.pos);
		bullet->Stop();

		if (firstBullet == nullptr)
		{
			firstBullet = bullet;
		}
		AddList(bullet);
		bCnt++;

		if (firstBullet->GetCircle().pos.x == bullet->GetCircle().pos.x &&
			firstBullet->GetCircle().pos.y == bullet->GetCircle().pos.y &&
			list.size() != 1)
		{
			_shotFlag = true;
		}
	}

	if (bCnt == 12)
	{
		_freamCnt++;
		firstBullet = nullptr;
		for (auto a : list)
		{
			a->SetPos(Vector2(a->GetCircle().pos.x, a->GetCircle().pos.y + -1));
		}
	}

	if (_freamCnt > 30)
	{
		Shot();
		DeleteList();
		bCnt = 0;
		_freamCnt = 0;
	}
}
