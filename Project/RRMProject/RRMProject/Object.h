#pragma once

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


public:
	Object();
	virtual ~Object();

	virtual ObjectType GetObjType();

	virtual void Hit(Player* other);
	virtual void Hit(Enemy* other);
	virtual void Hit(Block* other);
	virtual void Hit(Bullet* other);
};

