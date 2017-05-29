#pragma once

class Player;
class Enemy;
class Block;
class Bullet;


//“–‚½‚è”»’è—p
enum class ObjectType
{
	none,			//–³

	player,
	enemy,
	common,
};

class Object
{
private:

protected:
	int _handle;		//‰æ‘œƒnƒ“ƒhƒ‹


public:
	Object();
	virtual ~Object();

	virtual ObjectType GetObjType();

	virtual void Hit(Player* other);
	virtual void Hit(Enemy* other);
	virtual void Hit(Block* other);
	virtual void Hit(Bullet* other);
};

