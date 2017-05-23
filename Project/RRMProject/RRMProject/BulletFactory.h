#pragma once

#include <vector>
#include "Bullet.h"
#include "Player.h"

class BulletFactory
{
protected:
	//flyweightパターンを用い全部の弾を持つ
	std::vector<Bullet*> _bulletList;
	int _handle;
private:

public:
	BulletFactory();
	~BulletFactory();

	//戻り値　弾を生成又は使える弾のポインタを得る
	Bullet* GetBullet(const BulletType& bulletID,Vector2 vec,ObjectType type,
		Vector2 entry = Vector2(0,0));
	std::vector<Bullet*>& Getlist() { return _bulletList; }
	void Delete();
};

