#include "Digestion.h"

//�H�ו������Ă�����
const int FOOD_LIMIT = 3;

//���ʂ̃e�[�u�����쐬
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

	// if(ret.pow >= 3)  �U���͂��グ��
}