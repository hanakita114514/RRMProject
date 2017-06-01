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
	HitPoint _hp;			//�̗�

	PowerPoint _pp;			//�p���[�|�C���g
	Vector2 _vel;			//���x
	DInput _input;			//�C���v�b�g
	Digestion _dig;			//����
	SlowDown _sd;			//�x������

	PlayerState _ps;		//�v���C���[�̏��

	Vector2 _dir;			//�����i1�c�E�����A-1�c������)
	Vector2 _shootPos;		//�e�̔��ˈʒu
	Circle _grazePoint;		//�e�Ƃ̓����蔻��p�̈ʒu

	MultihitProtect _mhp;	//���i�q�b�g��h��

	Camera& _camera;

	int _nosedive;

	float _avoidTime;		//�������

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
	Player(int padType, Camera& camera);	//�g���p�b�h�ԍ����w��
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

