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
	HitPoint _hp;			//�̗�
	PowerPoint _pp;			//�p���[�|�C���g
	Vector2 _vel;			//���x
	DInput _input;			//�C���v�b�g
	Digestion _dig;			//����

	PlayerState _ps;
	Vector2 _dir;			//�����i1�c�E�����A-1�c������)
	Vector2 _shootPos;		//�e�̔��ˈʒu
	Circle _grazePoint;		//�e�Ƃ̓����蔻��p�̈ʒu

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
	Player(int padType);	//�g���p�b�h�ԍ����w��
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

