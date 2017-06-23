#include "Digestion.h"

//食べ物を持てる上限数
const int FOOD_LIMIT = 3;

//効果のテーブルを作成
const int foodTable[9][9] =
{

};

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

	// if(ret.pow >= 3)  攻撃力を上げる
}