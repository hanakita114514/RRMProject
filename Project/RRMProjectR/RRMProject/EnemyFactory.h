#pragma once

#include "Enemy.h"
#include <map>

enum class EnemyType
{
	none,

	mushroom,
	sushi,
	egg,
	tomato,
	hamburger,
	meat,

	num,
};
class EnemyFactory
{
private:
	std::map<EnemyType, int> _imgMap;

public:
	EnemyFactory();
	~EnemyFactory();

	Enemy* Create(const EnemyType& et, const Position& pos);
};

