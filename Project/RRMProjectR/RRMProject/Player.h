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
	HitPoint _hp;			//�̗�

	PowerPoint _pp;			//�p���[�|�C���g
	Vector2 _vel;			//���x
	DInput _input;			//�C���v�b�g
	Digestion _dig;			//����
	SlowDown _sd;			//�x������
	Armor _armor;			//�A�[�}�[
	PlayerHitBox _hitBox;

	PlayerState _ps;		//�v���C���[�̏��

	Vector2 _dir;			//�����i1�c�E�����A-1�c������)
	Vector2 _shootPos;		//�e�̔��ˈʒu
	BulletType _tool[ToolMax];

	MultihitProtect _mhp;	//���i�q�b�g��h��

	Camera& _camera;

	int _nosedive;
	int _toolIdx;

	float _avoidTime;		//�������
	float _invincibleTime;	//���G����
	float _attackTime;		//�U������

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

	//��������
	void DistanceAttenuation();


public:
	Player(int padType, Camera& camera);	//�g���p�b�h�ԍ����w��
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

