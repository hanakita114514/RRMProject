#pragma once

#include "Vector2.h"
#include "RectObj.h"
#include "MultihitProtect.h"
#include "HitPoint.h"
#include "AbstractSpell.h"
#include "Camera.h"
#include "HPBar.h"
#include "HitBox.h"
#include "EnemyHitBox.h"

enum class EnemyType
{
	none,

	mushroom,
	sushi,
	egg,
	tomato,
	hamburger,
	meat,

	num,
};

class Enemy	: public RectObj
{
protected:
	Vector2 _vel;			//速度
	float _friction;		//摩擦係数
	bool _hitGround;
	Vector2 _dir;
	bool _isAlive;
	Vector2 _uv;

	AbstractSpell* _absSpell;		//スペルファクトリー

	HitPoint _hp;
	MultihitProtect _mhp;	//多段ヒットを防ぐ

	HPBar _hpbar;

	void DistanceAttenuation();
	void Gravity();

	bool _isDamage;			//ダメージ喰らってる状態か？
	float _animFrame;		//アニメーション用フレーム

	EnemyHitBox* _hitBox;
	bool _footCheck;			//足元確認
	bool _isSearch;				//プレイヤーを見つけたか？

	virtual void Anim() = 0;				//アニメーション

	void ColDraw();				//当たり判定の描画
private:

public:
	Enemy();
	virtual ~Enemy();

	virtual void Initialize();

	virtual void Update() = 0;				//更新
	virtual void Draw(const Vector2& offset) = 0;				//描画

	virtual void ScreenLimit(Camera& camera);

	ObjectType GetObjType();
	Vector2 GetVel() { return _vel; }
	virtual EnemyType GetEnemyType();

	void SetHitGround(bool isHit) { _hitGround = isHit; }

	bool IsDead() { return !_isAlive; }
	void Destory();

	virtual void Hit(Block* other);
	virtual void Hit(Player* other);
	virtual void Hit(Bullet* other);
	virtual void Damage(float power, const Vector2& vec);

	bool IsHit() { return _hitGround; }

	EnemyHitBox*& GetHitBox() { return _hitBox; }
	MultihitProtect& GetHitProtect() { return _mhp; }

	void SetFootHit(bool flag);
	void SearchHit();

	void SearchClear();
};

