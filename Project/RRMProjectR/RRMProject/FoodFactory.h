#pragma once

#include "Food.h"
#include <map>

class FoodFactory
{
private:
	std::map<FoodType, int> _handleMap;
public:
	FoodFactory();
	~FoodFactory();

	Food* Create(FoodType type, const Position& pos, const Vector2& vel, double turnAngle);
};

