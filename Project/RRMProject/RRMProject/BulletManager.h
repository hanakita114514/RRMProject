#pragma once
#include "BulletFactory.h"
#include <vector>

class BulletManager
{
private:
	std::vector<Bullet*> *bullet;
	BulletFactory* _fac;

public:
	BulletManager();
	~BulletManager();

	void Update();
	void Draw();

	BulletFactory* GetFactory() { return _fac; }
};

