#pragma once
#include "Enemy.h"
#include "Circle.h"
#include "BulletManager.h"

const float ANIM_SPEED = 0.5;

enum ShootDir
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
	MAX
};

enum class EggState : unsigned int
{
	wait,
	shot,
	jump,
	coolTime,
	max
};

class Egg : public Enemy
{
private:
	int _shotCnt;				//発射カウント
	float _animCnt;				//アニメーションカウント
	Vector2 _uv;
	Vector2 _shotPos;
	Circle _circle;
	Vector2 _shootVec;
	int _freamCnt;
	float _searchTime;
	void Jump();

	Rect _territory;

	void (Egg::*_update)();

	void AliveUpdate();
	void DyingUpdate();
	void DamageUpdate();

	void Anim();

	EggState _state;

	using EggState = void (Egg::*)();

	EggState _stateUpdate[(int)EggState::max];
public:
	Egg(int handle, const Position& pos);
	~Egg();

	void Initialize();								//初期化
	void Update();									//更新
	void Draw(const Vector2& offset);				//描画
	void Move();

	void Shot();

	void Wait();

	void CoolTime();

	void Shot(BulletType type,int count = 0);		//攻撃

	//弱体化
	void Weakening();
};


