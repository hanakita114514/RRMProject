#pragma once

#include "Enemy.h"
#include <map>
#include "Spell.h"

class Hamburger :public Enemy
{
private:
	enum class Distance : unsigned int
	{
		d_near,
		d_medium,
		d_far,
	};

	enum class State : unsigned int
	{
		avoidance,
		jump_avoid,
		melee_attack,
		wait,
		shock_wave,
		aplysia,
		normal_bullet,
		summon,
	};

	enum class Update : unsigned int
	{
		alive,
		damage,
		dying,
	};

private:
	typedef void (Hamburger::*_func)();

	std::map<Distance, _func> _disUpdate;
	void NearUpdate();
	void MediumUpdate();
	void FarUpdate();
	Distance _dis;

	std::map<State, _func> _stateUpdate;
	State _state;
	void Avoidance();
	void JumpAvoid();
	void MeleeAttack();
	void Wait();
	void ShockWave();
	void Aplysia();		//è„ãÛÇ©ÇÁíeñãÇç~ÇÁÇπÇÈ
	void NormalBullet();
	void Summon();		//ìGè¢ä´

	std::map<Update, _func> _updateFunc;
	Update _update;
	void AliveUpdate();
	void DamageUpdate();
	void DyingUpdate();

	Spell* _spell;

	float _waitFrame;

public:
	Hamburger(int _handle, const Position& pos);
	~Hamburger();

	void Initialize();
	void Update();
	void Draw(const Position& offset);
	void Anim();
};

