#pragma once

#include "Enemy.h"
#include <vector>

class EnemyFactory
{
private:
	int _eggImg[3];

public:
	EnemyFactory();
	~EnemyFactory();

	Enemy* Create(const EnemyType& et, const Position& pos);
};

