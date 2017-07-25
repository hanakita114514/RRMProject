#pragma once
#include "Bullet.h"

//DropBullet�N���X
//�d�͂̉e�����󂯂�e
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

