#include "DropShot.h"
#include "BulletManager.h"

DropShot::DropShot()
{
	_bulletNum = 5;
}


DropShot::~DropShot()
{
}

void
DropShot::Create(Vector2 vec, Vector2 pos, Object* owner)
{
	_vec = vec;
	_vec.y -= _bulletNum;
	BulletManager::Instance().Create(BulletType::dropBullet, pos, _vec, owner->GetObjType(), Vector2(0, 0), owner);

	_bulletNum--;
	if (_bulletNum >= 0)
	{
		Create(vec,pos,owner);
	}

	_bulletNum = 5;
}
