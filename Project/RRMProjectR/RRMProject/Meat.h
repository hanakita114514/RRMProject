#pragma once
#include "Enemy.h"
class Meat : public Enemy
{
private:
	enum class State
	{
		wait,
		damage,
		shot,
		max
	};
	void(Meat::*_update)();

	void AlliveUpdate();
	void DamageUpdate();
	State _meatState;

	void Wait();
	void Damage();
	void Shot();

	using MeatState = void(Meat::*)();
	MeatState _state[(int)State::max] =
	{
		&Meat::Wait,
		&Meat::Damage,
		&Meat::Shot
	};

public:
	Meat();
	Meat(int handle);
	~Meat();

	void Initialize();
	void Update();
	void Draw(const Vector2& offset);
	void Anim();
};

