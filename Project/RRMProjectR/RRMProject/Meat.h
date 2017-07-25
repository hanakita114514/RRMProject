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
		attack,
		coolTime,
		max
	};
	void(Meat::*_update)();

	void AlliveUpdate();
	void DamageUpdate();
	void DyingUpdate();
	State _meatState;

	void Wait();
	void Jump();

	void Find();
	void Move();
	void Attack();
	void CoolTime();

	float _animCnt;
	float _frameCnt;
	using MeatState = void(Meat::*)();
	const MeatState _state[(int)State::max] =
	{
		&Meat::Wait,
		&Meat::Find,
		&Meat::Attack,
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

	void SearchHit(const Position& targetPos);
	void SearchFailed();
};

