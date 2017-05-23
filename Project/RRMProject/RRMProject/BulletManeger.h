#pragma once
#include "BulletFactory.h"
#include <vector>

class BulletManeger
{
private:
	std::vector<Bullet*> *bullet;
	BulletFactory* _fac;

public:
	BulletManeger();
	~BulletManeger();

	void Update();
	void Draw();

	BulletFactory* GetFactory() { return _fac; }
};

