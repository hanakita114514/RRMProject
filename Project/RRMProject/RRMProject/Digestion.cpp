#include "Digestion.h"

//H‚×•¨‚ðŽ‚Ä‚éãŒÀ”
const int FOOD_LIMIT = 3;

Digestion::Digestion()
{
}


Digestion::~Digestion()
{
}

void 
Digestion::Add(const Food& food)
{
	if (_foodList.size() >= FOOD_LIMIT)
	{
		_foodList.pop();
	}
	_foodList.push(food);
}

void
Digestion::Digest()
{
	Food::FoodStatus ret;
	while (!_foodList.empty())
	{
		ret.pow += _foodList.front().GetFoodStatus().pow;
		ret.defense += _foodList.front().GetFoodStatus().defense;
		ret.speed += _foodList.front().GetFoodStatus().speed;

		_foodList.pop();
	}

	// if(ret.pow >= 3)  UŒ‚—Í‚ðã‚°‚é
}