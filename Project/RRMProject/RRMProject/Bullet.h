#pragma once

#include "Vector2.h"
#include "CircleObj.h"

const int LIFE_DEF = 20;
//�e�̉摜�T�C�Y��24*24
//�e���̂̃T�C�Y��22*22�ɂ��Ă���܂�
const float BULLET_RADIUS = 22 / 2;		//���a

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

	Object* _owner;

public:
	Bullet();
	virtual ~Bullet();

	BulletType GetID();						//ID�̎擾
	bool IsAlive();						//�����Ă��邩�H
	virtual void Initialize(Vector2 vec, ObjectType type);				//������
	virtual void Update() = 0;						//�X�V
	virtual void Draw(const Vector2& offset) = 0;						//�`��
	ObjectType GetObjType();

	//�e���g�p�����L�����̃|�C���^��Ԃ�
	Object* GetOwner();
	void SetOwner(Object* obj);

	inline void Destory() { _isAlive = false; }

	void Hit(Player* otheer);
	void Hit(Enemy* other);
	void Hit(Block* other);

	Vector2 GetVel() { return _vel; }
};


