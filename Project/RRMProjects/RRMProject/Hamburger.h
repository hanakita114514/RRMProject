#pragma once
#include "Enemy.h"
class Hamburger :public Enemy
{
public:
	Hamburger();
	Hamburger(int _handle);
	~Hamburger();

	void Initialize();
	void Update();
	void Draw();
	void Anim();
};

