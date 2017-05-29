#pragma once

#include "Enemy.h"
class Mushroom : public Enemy
{
private:
public:
	Mushroom();
	Mushroom(int handle);
	~Mushroom();

	void Initialize();
	void Update();
	void Draw(const Vector2& offset);

	void Anim();
};

