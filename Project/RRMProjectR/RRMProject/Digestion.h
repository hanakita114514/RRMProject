#pragma once

#include <queue>
#include "Food.h"

enum class AlterationType
{
	none,
};

class Digestion
{
private:
	std::queue<Food*> _foodList;

public:
	Digestion();
	~Digestion();

	//食べ物を追加
	void Add(Food* food);

	//消化
	void Digest();

};

