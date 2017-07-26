#pragma once

#include "Enemy.h"
#include <map>
#include "Spell.h"
#include "Camera.h"

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
		none,
		avoidance,
		jump_avoid,

		melee_wait,
		melee_attack,
		
		near_wait,
		middle_wait,
		far_wait,
		shock_wave,
		aplysia,
		normal_bullet,
		summon,
		stroll,
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
	void MeleeWait();

	void ShockWave();
	void Aplysia();		//上空から弾幕を降らせる
	void NormalBullet();
	void Summon();		//敵召喚
	void Stroll();		//散歩

	void NearWait();
	void MiddleWait();
	void FarWait();
	void None();

	std::map<Update, _func> _updateFunc;
	Update _update;
	void AliveUpdate();
	void DamageUpdate();
	void DyingUpdate();

	Spell* _spell;

	float _waitFrame;
	float _strollTime;
	float _aplysiaTime;
	float _meleeTime;

	const Position& _playerPos;

	int _dir; //左にいるときプラス 右の場合マイナス

	Camera& _camera;

public:
	Hamburger(int _handle, const Position& pos, const Position& playerPos, Camera& camera);
	~Hamburger();

	void Initialize();
	void Update();
	void Draw(const Position& offset);
	void Anim();
};

