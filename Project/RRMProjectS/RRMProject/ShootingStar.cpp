#include "ShootingStar.h"
#include "BulletManager.h"
#include "Mathematics.h"
const float OFFSET = 100;
const float RADIUS = 64;
int stt = 0;
const int STT_MAX = 5;


ShootingStar::ShootingStar()
{
}


ShootingStar::~ShootingStar()
{
}

void
ShootingStar::Create(Vector2 vec, Vector2 pos, Object* owner)
{

	Circle circle = {};
	circle.pos = pos;
	circle.pos.y -= OFFSET;
	circle.radius = RADIUS;
	pos = circle.pos;
	pos.y -= circle.radius;

	Bullet* bullet = nullptr;
	BulletManager& bm = BulletManager::Instance();



	bullet = bm.Create(BulletType::normal, vec, owner->GetObjType(), Vector2(0, 0), owner);
}
