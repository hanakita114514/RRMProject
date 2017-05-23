#pragma once

#include <vector>
#include "Bullet.h"
#include "Player.h"

class BulletFactory
{
protected:
	//flyweight�p�^�[����p���S���̒e������
	std::vector<Bullet*> _bulletList;
	int _handle;
private:

public:
	BulletFactory();
	~BulletFactory();

	//�߂�l�@�e�𐶐����͎g����e�̃|�C���^�𓾂�
	Bullet* GetBullet(const BulletType& bulletID,Vector2 vec,ObjectType type,
		Vector2 entry = Vector2(0,0));
	std::vector<Bullet*>& Getlist() { return _bulletList; }
	void Delete();
};

