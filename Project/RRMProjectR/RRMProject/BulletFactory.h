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

	//戻り値　弾を生成又は使える弾のポインタを得る
	Bullet* Create(const BulletType& bulletID, const Position& pos, Vector2 vec, ObjectType type,
		Vector2 entry = Vector2(0, 0));

};

