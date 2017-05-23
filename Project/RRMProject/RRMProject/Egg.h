#pragma once
#include "Enemy.h"
const int IMAGE_NUM = 3;
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
	int _img[IMAGE_NUM];		//画像ハンドル
	int _animCnt;				//アニメーションカウント
	int suffix;
	int _junpCnt;
	Vector2 _shootPos[ShootDir::MAX];
	Circle _circle;
	Vector2 _shootVec;
	bool ret;
	int _freamCnt;

	void Jump();
public:
	Egg(int* handle);
	~Egg();

	void Initialize();			//初期化
	void Update();				//更新
	void Draw();				//描画
	void Anim();
	void Move();

	void Shot();

	void Wait();

	void(Egg::*_state)();

	void Shot(BulletType type,int count = 0);	//攻撃

	void ShotAngleCalc(Vector2 shootPos);

	virtual void Hit(Player* other);
	virtual void Hit(Block* other);

};

