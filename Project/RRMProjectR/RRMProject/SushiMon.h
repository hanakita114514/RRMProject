#pragma once

#include "Enemy.h"
#include "Collision.h"

class SushiMon : public Enemy
{
private:
	Collision _col;

	float _warryTime;

	void (SushiMon::*_update)();

	void AliveUpdate();
	void WorryUpdate();
	void FallUpdate();
	void DyingUpdate();
	void DamageUpdate();
public:
	SushiMon(int handle, const Position& pos);
	~SushiMon();

	void Initialize();

	void Update();
	void Draw(const Vector2& offset);
	void Anim();

	EnemyType GetEnemyType();
};

