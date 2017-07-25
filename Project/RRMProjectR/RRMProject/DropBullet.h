#pragma once
#include "Bullet.h"

//DropBulletƒNƒ‰ƒX
//d—Í‚Ì‰e‹¿‚ğó‚¯‚é’e
class DropBullet : public Bullet
{
public:
	DropBullet();
	DropBullet(int _handle);
	~DropBullet();

	void Initialize(const Position& pos, Vector2 vec, ObjectType type);
	void Draw(const Vector2& offset);
	void Update();
};

