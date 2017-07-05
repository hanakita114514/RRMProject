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
		jump,
	};
	std::map<PlayerState, int> _handleMap;

	static const int ToolMax = 3;
private:
	HitPoint _hp;			//�̗�
	PlayerHP _hpbar;		//�̗̓o�[

	PowerPoint _pp;			//�p���[�|�C���g
	Vector2 _vel;			//���x
	Input* _input;			//�C���v�b�g
	Digestion _dig;			//����
	SlowDown _sd;			//�x������
	Armor _armor;			//�A�[�}�[
	PlayerHitBox _hitBox;	//�����蔻��
	MultihitProtect _mhp;	//���i�q�b�g��h��

	PlayerState _ps;		//�v���C���[�̏��

	Vector2 _dir;			//�����i1�c�E�����A-1�c������)
	Vector2 _shootPos;		//�e�̔��ˈʒu
	BulletType _tool[ToolMax];

	Camera& _camera;

	int _animFrame;

	int _nosedive;
	int _toolIdx;

	float _avoidTime;		//�������
	float _invincibleTime;	//���G����
	float _attackTime;		//�U������

	bool _isJump;		//�W�����v����?
	bool _groundJump;	//�n��W�����v
	bool _hitGround;
	bool _secondJump;	//��i�W�����v���c���Ă��邩�H
	bool _isAirJump;	//�󒆃W�����v�����H

	bool _addAttackFlag;	//�ǉ��U���t���O

	float _speed;

	void Jump();
	void Move();

	void(Player::*_attack)();
	void FirstAttack();
	void SecondAttack();
	void ThirdAttack();
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
	bool _turnFlag;

	void HitGround();

	void ToolSwitch();
	void WeaponSwitch();

	//��������
	void DistanceAttenuation();


public:
	Player(int padType, Camera& camera, InputMode mode);	//�g���p�b�h�ԍ����w��
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
	void Damage(float power, HitBox hitBox);

	bool IsHitGround() { return _hitGround; }
	bool IsAvoidance();
	bool IsDamage();
	bool IsDead();

	std::vector<HitBox>& GetAttackBoxes() { return _hitBox.GetAttackBoxes(); }
	std::vector<HitBox>& GetDamageBoxes() { return _hitBox.GetDamageBoxes(); }
	
	MultihitProtect& GetHitProtect() { return _mhp; }

	HitPoint& GetHP() { return _hp; }
};

