#pragma once

#include <vector>
#include "Bullet.h"
#include "Player.h"

class BulletFactory
{
private:
	int _handle;

public:
	BulletFactory();
	~BulletFactory();

	//�߂�l�@�e�𐶐����͎g����e�̃|�C���^�𓾂�
	Bullet* Create(const BulletType& bulletID, Vector2 vec, ObjectType type,
		Vector2 entry = Vector2(0, 0));

};
