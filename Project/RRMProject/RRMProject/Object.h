#pragma once

class Player;
class Enemy;
class Block;
class Bullet;

//当たり判定用
enum class ObjectType
{
	none,			//無

	player,
	enemy,
	common,
};

class Object
{
private:

protected:
	int _handle;		//画像ハンドル

public:
	Object();
	virtual ~Object();

	virtual ObjectType GetObjType();

	virtual void Hit(Player* other);
	virtual void Hit(Enemy* other);
	virtual void Hit(Block& other);
	virtual void Hit(Bullet* other);
};

