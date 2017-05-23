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
	std::queue<Food> _foodList;

public:
	Digestion();
	~Digestion();

	//H‚×•¨‚ğ’Ç‰Á
	void Add(const Food& food);

	//Á‰»
	void Digest();

};

