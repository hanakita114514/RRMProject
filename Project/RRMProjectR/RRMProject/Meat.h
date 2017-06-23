#pragma once
#include "Enemy.h"
class Meat : public Enemy
{
public:
	Meat();
	Meat(int handle);
	~Meat();

	void Initialize();
	void Update();
	void Draw();
	void Anim();
};

