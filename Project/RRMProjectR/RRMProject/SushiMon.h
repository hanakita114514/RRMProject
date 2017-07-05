#pragma once

#include "Enemy.h"
#include "Collision.h"

class SushiMon : public Enemy
{
private:
	Collision _col;

	float _warryTime;
	float _chargeTime;
	float _searchTime;

	void (SushiMon::*_update)();

	void AliveUpdate();
	void WorryUpdate();
	void SearchUpdate();
	void AttackUpdate();
	void ChargeUpdate();
	void FallUpdate();
	void DyingUpdate();
	void DamageUpdate();

	void Anim();

public:
	SushiMon(int handle, const Position& pos);
	~SushiMon();

	void Initialize();

	void Update();
	void Draw(const Vector2& offset);

	EnemyType GetEnemyType();
};

