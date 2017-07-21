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
		coolTime,
		max
	};
	void(Meat::*_update)();

	void AlliveUpdate();
	void DamageUpdate();
	void DyingUpdate();
	State _meatState;

	void Wait();

	void Find();
	void Move();
	void CoolTime();

	float _animCnt;
	using MeatState = void(Meat::*)();
	const MeatState _state[(int)State::max] =
	{
		&Meat::Wait,
		&Meat::Find,
		&Meat::CoolTime
	};

	int _coolCnt;
	bool _isPlayEffect;

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

