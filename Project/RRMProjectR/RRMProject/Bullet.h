#pragma once

#include "Vector2.h"
#include "CircleObj.h"
#include "GameTime.h"

const int LIFE_DEF = 20;

//�e�̉摜�T�C�Y��24*24
//�e���̂̃T�C�Y��24*24�ɂ��Ă���܂�
const float BULLET_RADIUS = 24 / 2;		//���a

enum class BulletType
{
	none,
	normal,					//�ʏ�e
	homing,					//�z�[�~���O�e
	sinBullet,
	lazer,
	bezier,					//�x�W�F�Ȑ��e
	deffusion,				//�g�U
	circleBullet,			//���ˏ�ɔ��
	rainBullet,				//�J�̂悤�ɗ�����
	//�����ɒǉ�

	num,
};

class Bullet : public CircleObj
{
protected:
	BulletType _id;		//�e�̎��
	Vector2 _vel;	//�e�̑��x
	bool _isAlive;	//�����Ă��邩�H
	ObjectType _objType;	//�G�A�v���C���[�̋�ʂ̃^�C�v
	float _life;				//�e�̎���
	float _pow;					//�U����

	Object* _owner;

	bool _isHitGround;
protected:
	enum class BulletState
	{
		move,
		stop
	};

	BulletState _bs;

public:
	Bullet();
	virtual ~Bullet();

	GameTime& _gameTime;

	BulletType GetID();						//ID�̎擾
	bool IsAlive();						//�����Ă��邩�H
	virtual void Initialize(const Position& pos, Vector2 vec, ObjectType type);				//������
	virtual void Update() = 0;						//�X�V
	virtual void Draw(const Vector2& offset) = 0;						//�`��
	virtual void Finalize();
	ObjectType GetObjType();

	//�e���g�p�����L�����̃|�C���^��Ԃ�
	Object* GetOwner();
	void SetOwner(Object* obj);

	void Destory() { _isAlive = false; }
	void HitGround();

	void LifeDecrease();	//���C�t�����炷

	void Hit(Player* otheer);
	void Hit(Enemy* other);
	void Hit(Block* other);
	void Hit(Bullet* other);

	Vector2 GetVel() { return _vel; }
	float GetPower() { return _pow; }

	void Stop() { _bs = BulletState::stop; }
	void Move() { _bs = BulletState::move; }
};


