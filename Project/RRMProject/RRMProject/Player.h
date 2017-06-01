#pragma once

#include "RectObj.h"
#include "DInput.h"
#include "Digestion.h"
#include "HitPoint.h"
#include "PowerPoint.h"
#include "Circle.h"

#include "SlowDown.h"
#include "MultihitProtect.h"
#include "Camera.h"


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
	SlowDown _sd;			//遅くする

	PlayerState _ps;		//プレイヤーの状態

	Vector2 _dir;			//向き（1…右向き、-1…左向き)
	Vector2 _shootPos;		//弾の発射位置
	Circle _grazePoint;		//弾との当たり判定用の位置

	MultihitProtect _mhp;	//多段ヒットを防ぐ

	Camera& _camera;

	int _nosedive;

	float _avoidTime;		//回避時間

	bool _isJump;
	bool _hitGround;
	bool _secondJump;
	bool _isAirJump;

	float _speed;

	void Jump();
	void Move();

	void (Player::*_update)();
	void AliveUpdate();
	void AvoidanceUpdate();
	void DamageUpdate();
	void DyingUpdate();

	void (Player::*_state)();
	void AttackState();
	void NeutralState();
	void ShootState();

	void (Player::*_isdir)();
	void DirRight();
	void DirLeft();

	void HitGround();

public:
	Player(int padType, Camera& camera);	//使うパッド番号を指定
	~Player();

	void Init();
	void Update();
	void Draw();

	void SetHitGround(bool isHit) { _hitGround = isHit; }

	ObjectType GetObjType();
	Vector2 GetVel() { return _vel; }
	Vector2 GetDir() { return _dir; }

	Circle GetGraze() { return _grazePoint; }

	void SlowMotion();

	void Hit(Enemy* other);
	void Hit(Block* other);
	void Hit(Bullet* other);


	bool IsHitGround() { return _hitGround; }
};

