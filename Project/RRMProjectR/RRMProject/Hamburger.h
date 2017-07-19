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

	Spell* _spell;

public:
	Hamburger(int _handle, const Position& pos);
	~Hamburger();

	void Initialize();
	void Update();
	void Draw(const Position& offset);
	void Anim();
};

