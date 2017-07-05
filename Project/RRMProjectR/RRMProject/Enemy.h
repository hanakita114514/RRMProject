#pragma once

#include "Vector2.h"
#include "RectObj.h"
#include "MultihitProtect.h"
#include "HitPoint.h"
#include "AbstractSpell.h"
#include "Camera.h"
#include "HPBar.h"
#include "HitBox.h"
#include "EnemyHitBox.h"

enum class EnemyType
{
	none,

	mushroom,
	sushi,
	egg,
	tomato,
	hamburger,
	meat,

	num,
};

class Enemy	: public RectObj
{
protected:
	Vector2 _vel;			//���x
	float _friction;		//���C�W��
	bool _hitGround;
	Vector2 _dir;
	bool _isAlive;
	Vector2 _uv;

	AbstractSpell* _absSpell;		//�X�y���t�@�N�g���[

	HitPoint _hp;
	MultihitProtect _mhp;	//���i�q�b�g��h��

	HPBar _hpbar;

	void DistanceAttenuation();
	void Gravity();

	bool _isDamage;			//�_���[�W�����Ă��Ԃ��H
	float _animFrame;		//�A�j���[�V�����p�t���[��

	EnemyHitBox* _hitBox;
	bool _footCheck;			//�����m�F
	bool _isSearch;				//�v���C���[�����������H

	virtual void Anim() = 0;				//�A�j���[�V����

	void ColDraw();				//�����蔻��̕`��
private:

public:
	Enemy();
	virtual ~Enemy();

	virtual void Initialize();

	virtual void Update() = 0;				//�X�V
	virtual void Draw(const Vector2& offset) = 0;				//�`��

	virtual void ScreenLimit(Camera& camera);

	ObjectType GetObjType();
	Vector2 GetVel() { return _vel; }
	virtual EnemyType GetEnemyType();

	void SetHitGround(bool isHit) { _hitGround = isHit; }

	bool IsDead() { return !_isAlive; }
	void Destory();

	virtual void Hit(Block* other);
	virtual void Hit(Player* other);
	virtual void Hit(Bullet* other);
	virtual void Damage(float power, const Vector2& vec);

	bool IsHit() { return _hitGround; }

	EnemyHitBox*& GetHitBox() { return _hitBox; }
	MultihitProtect& GetHitProtect() { return _mhp; }

	void SetFootHit(bool flag);
	void SearchHit();

	void SearchClear();
};

