#pragma once
#include "Bullet.h"
#include <vector>
//í èÌíe--------------------------------------

class NormalBullet : public Bullet
{
private:
	int _freamCnt;
public:
	NormalBullet(int handle);
	~NormalBullet();

	void Initialize(const Position& pos, Vector2 vec, ObjectType type);
	void Update();
	void Draw(const Vector2& offset);
};

