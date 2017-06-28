#pragma once

#include "Vector2.h"
#include "HitStop.h"

class Player;
class Enemy;
class Block;
class Bullet;


//�����蔻��p
enum class ObjectType
{
	none,			//��

	player,
	enemy,
	common,
};

class Object
{
private:

protected:
	int _handle;		//�摜�n���h��
	bool _deleteFlag;	//�I���ɂȂ��������

	HitStop _hitStop;

public:
	Object();
	virtual ~Object();

	virtual ObjectType GetObjType();
	virtual Position& GetPosition() { return Position(0, 0); }

	//�����t���O�������Ă��邩�H
	bool IsDelete() { return _deleteFlag; }

	virtual void Hit(Player* other);
	virtual void Hit(Enemy* other);
	virtual void Hit(Block* other);
	virtual void Hit(Bullet* other);

	//�q�b�g�X�g�b�v
	virtual void HitStop(float time);
	//��̉�
	virtual void Weakening();

};

