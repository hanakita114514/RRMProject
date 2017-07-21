#pragma once
#include "Enemy.h"
#include "Territory.h"


class Meat : public Enemy
{
private:
	enum class State
	{
		wait,
		find,
		max
	};
	void(Meat::*_update)();

	void AlliveUpdate();
	void DamageUpdate();
	State _meatState;

	void Wait();

	void Find();
	void Move();

	float _animCnt;
	using MeatState = void(Meat::*)();
	const MeatState _state[(int)State::max] =
	{
		&Meat::Wait,
		&Meat::Find
	};

	Territory _territory;

public:
	Meat();
	Meat(int handle,Vector2 pos);
	~Meat();

	void Initialize();
	void Update();
	void Draw(const Vector2& offset);
	void Anim();
};

