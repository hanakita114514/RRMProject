#pragma once

#include "Enemy.h"
#include <map>
#include "Camera.h"

class EnemyFactory
{
private:
	std::map<EnemyType, int> _imgMap;

public:
	EnemyFactory();
	~EnemyFactory();

	Enemy* Create(const EnemyType& et, const Position& pos);
	Enemy* Create(const EnemyType& et, const Position& pos, const Position& playerPos, Camera& camera);
};

