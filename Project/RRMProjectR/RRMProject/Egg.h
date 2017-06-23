#pragma once
#include "Enemy.h"
#include "Circle.h"
#include "BulletManager.h"
#include "HPBar.h"

const float ANIM_SPEED = 0.5;

enum ShootDir
{
	UP,
	RIGHT,
	DOWN,
	LEFT,
	MAX
};

class Egg : public Enemy
{
private:
	int _shotCnt;				//発射カウント
	float _animCnt;				//アニメーションカウント
	Vector2 _uv;
	int suffix;
	int _junpCnt;
	Vector2 _shootPos[ShootDir::MAX];
	Vector2 _shotPos;
	Circle _circle;
	Vector2 _shootVec;
	bool ret;
	int _freamCnt;

	HPBar _hpbar;

	void Jump();

	void (Egg::*_update)();

	void AliveUpdate();
	void DyingUpdate();

public:
	Egg(int handle, const Position& pos);
	~Egg();

	void Initialize();								//初期化
	void Update();									//更新
	void Draw(const Vector2& offset);				//描画
	void Anim();
	void Move();

	void Shot();

	void Wait();

	void(Egg::*_state)();

	void Shot(BulletType type,int count = 0);		//攻撃

	void ShotAngleCalc(Vector2 shootPos);

	//弱体化
	void Weakening();

};

