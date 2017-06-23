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

	//�H�ו���ǉ�
	void Add(const Food& food);

	//����
	void Digest();

};

