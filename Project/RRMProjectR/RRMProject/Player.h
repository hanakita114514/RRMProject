#pragma once

#include "RectObj.h"
#include "Digestion.h"
#include "HitPoint.h"
#include "PowerPoint.h"
#include "Circle.h"
#include "SlowDown.h"
#include "Camera.h"
#include "Armor.h"
#include "Bullet.h"
#include "PlayerHitBox.h"
#include "PlayerHP.h"
#include "Input.h"
#include "MultihitProtect.h"
#include "PlayerHP.h"
#include "Jump.h"
#include "PlayerDraw.h"
#include "Combo.h"

#include <map>


class Player : public RectObj
{
private:
	enum class UpdateState : unsigned int
	{
		alive,
		dying,
		attack,
		invincible,
		damage,
		avoidance,
	};

	enum class AttackState : unsigned int
	{
		first,
		second,
		third,
		up,
	};

	enum class Dir : unsigned int
	{
		right,
		left
	};

	static const int ToolMax = 3;
private:
	HitPoint _hp;			//体力
	PlayerHP _hpbar;		//体力バー

	Combo _combo;

	Jump _jump;

	PowerPoint _pp;			//パワーポイント
	Vector2 _vel;			//速度
	Input* _input;			//インプット
	Digestion _dig;			//消化
	SlowDown _sd;			//遅くする
	Armor _armor;			//アーマー
	PlayerHitBox _hitBox;	//当たり判定
	MultihitProtect _mhp;	//多段ヒットを防ぐ

	UpdateState _us;		//アップデートステート
	AttackState _as;		//アタックステート
	PlayerState _ps;		//プレイヤーの状態

	Vector2 _dir;			//向き（1…右向き、-1…左向き)
	Vector2 _shootPos;		//弾の発射位置
	BulletType _tool[ToolMax];

	Camera& _camera;

	PlayerDraw _playerDraw;

	int _animFrame;

	int _nosedive;
	int _toolIdx;

	float _avoidTime;		//回避時間
	float _invincibleTime;	//無敵時間
	float _attackTime;		//攻撃時間

	bool _hitGround;

	bool _addAttackFlag;	//追加攻撃フラグ

	float _speed;

	void Jump();
	void Move();

	typedef void(Player::*_func)();

	std::map<AttackState, _func> _attack;
	void FirstAttack();
	void SecondAttack();
	void ThirdAttack();
	void UpAttack();
	void DonwAttack();

	std::map<UpdateState, _func> _update;
	void AttackUpdate();
	void AliveUpdate();
	void AvoidanceUpdate();
	void DamageUpdate();
	void DyingUpdate();
	void InvincibleUpdate();

	void Shoot();

	void DirRight();
	void DirLeft();

	bool _turnFlag;

	void HitGround();

	void ToolSwitch();
	void WeaponSwitch();

	//戻り値 回避できたか？
	bool Avoidance();

	//距離減衰
	void DistanceAttenuation();

	//リソースの読み込み
	void LoadResources();

	//マップ初期化
	void MapInit();

public:
	Player(int padType, Camera& camera, InputMode mode);	//使うパッド番号を指定
	~Player();

	void Init();
	void Update();
	void SlowDownUpdate();
	void Draw();
	void UIDraw();

	void SetHitGround(bool isHit) { _hitGround = isHit; }

	ObjectType GetObjType();
	Vector2& GetVel() { return _vel; }
	Vector2& GetDir() { return _dir; }

	void SlowMotion();
	void SlowMotion(Object* other);

	void Hit(Enemy* other);
	void Hit(Block* other);
	void Hit(Bullet* other);

	void Damage(float power);
	void Damage(float power, HitBox hitBox);

	bool IsHitGround() { return _hitGround; }
	bool IsAvoidance();
	bool IsDamage();
	bool IsDead();

	std::vector<HitBox>& GetAttackBoxes() { return _hitBox.GetAttackBoxes(); }
	std::vector<HitBox>& GetDamageBoxes() { return _hitBox.GetDamageBoxes(); }

	MultihitProtect& GetHitProtect() { return _mhp; }

	Combo& GetCombo() { return _combo; }
};

