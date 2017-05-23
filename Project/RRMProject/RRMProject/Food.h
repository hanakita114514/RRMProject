#pragma once

#include "RectObj.h"

enum class FoodType
{
	none,

	//�����ɒǉ�

	num,
};

class Food	: public RectObj
{
public:
	struct FoodStatus
	{
		int pow;
		int speed;
		int defense;
	};
protected:
	FoodStatus _fs;

public:
	Food();
	virtual ~Food();

	virtual FoodStatus GetFoodStatus();

};

