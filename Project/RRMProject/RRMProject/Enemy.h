#pragma once

#include "Vector2.h"
#include "RectObj.h"
#include "BulletManeger.h"

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
	BulletManeger* _bMng;
	bool _hitGround;
	Vector2 _dir;

private:

public:
	Enemy();
	virtual ~Enemy();

	virtual void Initialize();

	virtual void Update() = 0;				//�X�V
	virtual void Draw() = 0;				//�`��
	virtual void Anim() = 0;				//�A�j���[�V����
	ObjectType GetObjType();
	Vector2 GetVel() { return _vel; }

	void SetHitGround(bool isHit) { _hitGround = isHit; }
};

