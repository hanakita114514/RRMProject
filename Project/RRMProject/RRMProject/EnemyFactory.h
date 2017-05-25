#pragma once

#include "Enemy.h"
#include <vector>

class EnemyFactory
{
private:
	int _eggImg[3];
	std::vector<Enemy*> _enemyList;

public:
	EnemyFactory();
	~EnemyFactory();

	Enemy* Create(const EnemyType& et);
	std::vector<Enemy*>& GetEnemyList() { return _enemyList; }
};

