#pragma once
#include "Enemy.h"
class Meat : public Enemy
{
private:
	void(Meat::*_update)();

	void AlliveUpdate();
	void DamageUpdate();

	void (Meat::*_state)();
	void Wait();
	void Damage();
	void Shot();
public:
	Meat();
	Meat(int handle);
	~Meat();


	void Initialize();
	void Update();
	void Draw(const Vector2& offset);
	void Anim();
};

