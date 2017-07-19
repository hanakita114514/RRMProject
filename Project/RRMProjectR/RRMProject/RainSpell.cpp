#include "RainSpell.h"
#include "BulletManager.h"
#include "common.h"

RainSpell::RainSpell()
{
}


RainSpell::~RainSpell()
{
}

void 
RainSpell::Create(Vector2 vec, Vector2 pos, Object* owner)
{
	BulletManager& bm = BulletManager::Instance();

	if (((int)_frameCnt % 20) == 0)
	{
		bm.Create(BulletType::rainBullet, Position((int)_frameCnt % WINDOW_WIDTH, 0), _vec, owner->GetObjType(), Vector2(0, 0), owner);
	}

	++_frameCnt;
}
