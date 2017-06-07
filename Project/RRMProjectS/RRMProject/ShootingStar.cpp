#include "ShootingStar.h"
#include "BulletManager.h"
const float OFFSET = 100;
const float RADIUS = 64;
const float PI = 3.141592;
const float RAD = PI / 180;
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
	circle.center = pos;
	circle.pos.y -= OFFSET;
	circle.radius = RADIUS;
	pos = circle.center;
	pos.y -= circle.radius;

	Bullet* bullet = nullptr;
	BulletManager& bm = BulletManager::Instance();



	bullet = bm.Create(BulletType::normal, vec, owner->GetObjType(), Vector2(0, 0), owner);
}
