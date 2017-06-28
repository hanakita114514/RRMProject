#pragma once

#include "Vector2.h"
#include "HitStop.h"

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
	bool _deleteFlag;	//オンになったら消す

	HitStop _hitStop;

public:
	Object();
	virtual ~Object();

	virtual ObjectType GetObjType();
	virtual Position& GetPosition() { return Position(0, 0); }

	//消すフラグが立っているか？
	bool IsDelete() { return _deleteFlag; }

	virtual void Hit(Player* other);
	virtual void Hit(Enemy* other);
	virtual void Hit(Block* other);
	virtual void Hit(Bullet* other);

	//ヒットストップ
	virtual void HitStop(float time);
	//弱体化
	virtual void Weakening();

};

