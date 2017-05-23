#pragma once

#include "RectObj.h"
#include "DInput.h"
#include "Digestion.h"
#include "HitPoint.h"
#include "PowerPoint.h"
#include "Circle.h"

#include <map>

class Player : public RectObj
{
private:
	enum class PlayerState
	{
		none,

		neutral,
		walk,
		attack,
		shoot,
		avoidance,

	};
	std::map<PlayerState, int> _handleMap;

private:
	HitPoint _hp;			//体力
	PowerPoint _pp;			//パワーポイント
	Vector2 _vel;			//速度
	DInput _input;			//インプット
	Digestion _dig;			//消化

	PlayerState _ps;
	Vector2 _dir;			//向き（1…右向き、-1…左向き)
	Vector2 _shootPos;		//弾の発射位置
	Circle _grazePoint;		//弾との当たり判定用の位置

	bool _isJump;
	bool _hitGround;
	bool _secondJump;
	bool _isAirJump;

	float _speed;

	void Jump();
	void Move();

	void (Player::*_update)();
	void(Player::*_isdir)();

	void AliveUpdate();
	void DyingUpdate();

	void (Player::*_state)();
	void Attack();
	void Avoidance();
	void Neutral();
	void Shoot();

	void DirRight();
	void DirLeft();

public:
	Player(int padType);	//使うパッド番号を指定
	~Player();

	void Init();
	void Update();
	void Draw();

	void SetHitGround(bool isHit) { _hitGround = isHit; }

	ObjectType GetObjType();
	Vector2 GetVel() { return _vel; }

	Circle GetGraze() { return _grazePoint; }

	virtual void Hit(Enemy* other);
	virtual void Hit(Block* other);
	virtual void Hit(Bullet* other);
};

