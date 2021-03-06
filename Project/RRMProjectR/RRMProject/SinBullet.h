#pragma once
#include "Bullet.h"

class SinBullet : public Bullet
{
private:

	int _freamCnt;
	bool _returnFlag;
public:
	SinBullet(int handle);
	~SinBullet();

	virtual void Initialize(const Position& pos, Vector2 vec, ObjectType type);				//初期化
	void Update();					//更新
	void Draw(const Vector2& offset);					//描画

	void Move();					//移動
	void LifeDecrease();				//ライフの減算

	void Return(bool flag) { _returnFlag = flag; }
};

