#pragma once

#include "Enemy.h"
class Mushroom : public Enemy
{
private:

	void (Mushroom::*_update)();
	void AliveUpdate();
	void DyingUpdate();

	void Anim();

public:
	Mushroom(int handle, const Position& pos);
	~Mushroom();

	void Initialize();
	void Update();
	void Draw(const Vector2& offset);

};

