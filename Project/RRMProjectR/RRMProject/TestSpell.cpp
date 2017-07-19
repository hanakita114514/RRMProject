#include "TestSpell.h"
#include "BulletManager.h"
#include "SinBullet.h"

TestSpell::TestSpell()
{
}


TestSpell::~TestSpell()
{
}

void TestSpell::Create(Vector2 vec, Vector2 pos, Object *owner)
{
	const float DefaultAngle = 60;
	_frameCnt++;

		_pos = pos;
		_vec = vec;
		Bullet* bullet = nullptr;
		BulletManager& bm = BulletManager::Instance();

			bullet = bm.Create(BulletType::normal, _pos, _vec, ObjectType::enemy, Vector2(0, 0), owner);
			bullet->SetPos(_pos);

			for (int i = 0; i < 2; i++)
			{
				bullet = bm.Create(BulletType::sinBullet, _pos, _vec, ObjectType::enemy, Vector2(0, 0), owner);
				bullet->SetPos(_pos);
				if (i == 1)
				{
					dynamic_cast<SinBullet*>(bullet)->Return(true);
				}
			}

}
