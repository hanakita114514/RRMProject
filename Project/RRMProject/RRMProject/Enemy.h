#pragma once

#include "Vector2.h"
#include "RectObj.h"

enum class EnemyType
{
	none,
	egg,
	mushroom,
	//ここに追加

	num,
};

class Enemy	: public RectObj
{
protected:
	Vector2 _vel;			//速度
	bool _hitGround;
	Vector2 _dir;

private:

public:
	Enemy();
	virtual ~Enemy();

	virtual void Initialize();

	virtual void Update() = 0;				//更新
	virtual void Draw() = 0;				//描画
	virtual void Anim() = 0;				//アニメーション
	ObjectType GetObjType();
	Vector2 GetVel() { return _vel; }

	void SetHitGround(bool isHit) { _hitGround = isHit; }
};

