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
#include "Armor.h"
#include "Bullet.h"
#include "PlayerHitBox.h"

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
		invincible,
		damage,
	};
	std::map<PlayerState, int> _handleMap;

	static const int ToolMax = 3;
private:
	HitPoint _hp;			//体力

	PowerPoint _pp;			//パワーポイント
	Vector2 _vel;			//速度
	DInput _input;			//インプット
	Digestion _dig;			//消化
	SlowDown _sd;			//遅くする
	Armor _armor;			//アーマー
	PlayerHitBox _hitBox;

	PlayerState _ps;		//プレイヤーの状態

	Vector2 _dir;			//向き（1…右向き、-1…左向き)
	Vector2 _shootPos;		//弾の発射位置
	BulletType _tool[ToolMax];

	MultihitProtect _mhp;	//多段ヒットを防ぐ

	Camera& _camera;

	int _nosedive;
	int _toolIdx;

	float _avoidTime;		//回避時間
	float _invincibleTime;	//無敵時間
	float _attackTime;		//攻撃時間

	bool _isJump;
	bool _hitGround;
	bool _secondJump;
	bool _isAirJump;

	float _speed;

	void Jump();
	void Move();

	void(Player::*_attack)();
	void FirstAttack();
	void SecondAttack();
	void UpAttack();
	void DonwAttack();

	void (Player::*_update)();
	void AttackUpdate();
	void AliveUpdate();
	void AvoidanceUpdate();
	void DamageUpdate();
	void DyingUpdate();
	void InvincibleUpdate();

	void Shoot();

	void (Player::*_isdir)();
	void DirRight();
	void DirLeft();

	void HitGround();

	void ToolSwitch();
	void WeaponSwitch();

	//距離減衰
	void DistanceAttenuation();


public:
	Player(int padType, Camera& camera);	//使うパッド番号を指定
	~Player();

	void Init();
	void Update();
	void Draw();

	void SetHitGround(bool isHit) { _hitGround = isHit; }

	ObjectType GetObjType();
	Vector2& GetVel() { return _vel; }
	Vector2& GetDir() { return _dir; }

	void SlowMotion();

	void Hit(Enemy* other);
	void Hit(Block* other);
	void Hit(Bullet* other);

	void Damage(float power);

	bool IsHitGround() { return _hitGround; }
	bool IsAvoidance();
	bool IsDamage();

	PlayerHitBox& GetHitBox() { return _hitBox; }
};

