#pragma once

#include "Vector2.h"
#include "RectObj.h"
#include "MultihitProtect.h"
#include "HitPoint.h"


enum class EnemyType
{
	none,
	egg,
	mushroom,
	//�����ɒǉ�

	num,
};

class Enemy	: public RectObj
{
protected:
	Vector2 _vel;			//���x
	bool _hitGround;
	Vector2 _dir;
	bool _isAlive;

	HitPoint _hp;
	MultihitProtect _mhp;	//���i�q�b�g��h��

private:

public:
	Enemy();
	virtual ~Enemy();

	virtual void Initialize();

	virtual void Update() = 0;				//�X�V
	virtual void Draw(const Vector2& offset) = 0;				//�`��
	virtual void Anim() = 0;				//�A�j���[�V����

	ObjectType GetObjType();
	Vector2 GetVel() { return _vel; }

	void SetHitGround(bool isHit) { _hitGround = isHit; }

	bool IsDead() { return !_isAlive; }

	virtual void Hit(Block* other);
	virtual void Hit(Player* other);
	virtual void Hit(Bullet* other);

	bool IsHit() { return _hitGround; }
};
