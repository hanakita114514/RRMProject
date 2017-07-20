#include "RainSpell.h"
#include "BulletManager.h"
#include "common.h"

RainSpell::RainSpell()
{
	_offset = 0;
	_vec = Vector2(1, 0);
}


RainSpell::~RainSpell()
{
}

void 
RainSpell::Create(Vector2 vec, Vector2 pos, Object* owner)
{
	BulletManager& bm = BulletManager::Instance();

	while (_offset <= WINDOW_WIDTH)
	{
		bm.Create(BulletType::rainBullet, Position(_offset, 0), _vec, owner->GetObjType(), Vector2(0, 0), owner);
		_vec.x *= -1;
		_offset += 150;
	}
	_offset = 0;
}
