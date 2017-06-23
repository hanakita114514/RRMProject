#pragma once

#include "Enemy.h"
#include <map>

class EnemyFactory
{
private:
	std::map<EnemyType, int> _imgMap;

public:
	EnemyFactory();
	~EnemyFactory();

	Enemy* Create(const EnemyType& et, const Position& pos);
};

