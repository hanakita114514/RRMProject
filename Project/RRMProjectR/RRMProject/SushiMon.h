#pragma once

#include "Enemy.h"
#include "Collision.h"
#include <map>

class SushiMon : public Enemy
{
private:
	enum class UpdateState
	{
		alive,
		worry,
		search,
		attack,
		fall,
		dying,
		damage,
		charge,
	};
private:
	Collision _col;

	float _warryTime;
	float _chargeTime;
	float _searchTime;

	typedef void (SushiMon::*_func)();

	std::map<UpdateState, _func> _update;
	void AliveUpdate();
	void WorryUpdate();
	void SearchUpdate();
	void AttackUpdate();
	void ChargeUpdate();
	void FallUpdate();
	void DyingUpdate();
	void DamageUpdate();
	UpdateState _state;

	void Anim();

public:
	SushiMon(int handle, const Position& pos);
	~SushiMon();

	void Initialize();

	void Update();
	void Draw(const Vector2& offset);

	EnemyType GetEnemyType();
};

