#pragma once
#include "Bullet.h"

//DropBulletクラス
//重力の影響を受ける弾
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

