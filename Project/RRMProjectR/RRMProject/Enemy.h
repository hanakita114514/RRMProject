#pragma once

#include "Vector2.h"
#include "RectObj.h"
#include "MultihitProtect.h"
#include "HitPoint.h"
#include "AbstractSpell.h"
#include "Camera.h"


class Enemy	: public RectObj
{
protected:
	Vector2 _vel;			//速度
	bool _hitGround;
	Vector2 _dir;
	bool _isAlive;
	Vector2 _uv;

	AbstractSpell* _absSpell;		//スペルファクトリー

	HitPoint _hp;
	MultihitProtect _mhp;	//多段ヒットを防ぐ

	void DistanceAttenuation();

	bool _isDamage;			//ダメージ喰らってる状態か？
	float _animFrame;		//アニメーション用フレーム
private:

public:
	Enemy();
	virtual ~Enemy();

	virtual void Initialize();

	virtual void Update() = 0;				//更新
	virtual void Draw(const Vector2& offset) = 0;				//描画
	virtual void Anim() = 0;				//アニメーション

	virtual void ScreenLimit(Camera& camera);

	ObjectType GetObjType();
	Vector2 GetVel() { return _vel; }

	void SetHitGround(bool isHit) { _hitGround = isHit; }

	bool IsDead() { return !_isAlive; }

	virtual void Hit(Block* other);
	virtual void Hit(Player* other);
	virtual void Hit(Bullet* other);
	virtual void Damage(float power, const Vector2& vec);

	bool IsHit() { return _hitGround; }
};

