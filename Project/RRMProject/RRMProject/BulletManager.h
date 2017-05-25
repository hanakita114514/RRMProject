#pragma once
#include "BulletFactory.h"
#include <vector>
#include "BulletFactory.h"

class BulletManager
{
private:
	std::vector<Bullet*> *bullet;
	BulletFactory _fac;

	BulletManager();
	BulletManager(const BulletManager&);
	BulletManager& operator = (const BulletManager&);
public:
	~BulletManager();

	static BulletManager& Instance()
	{
		static BulletManager instance;
		return instance;
	}

	void Update();
	void Draw();

	BulletFactory* GetFactory() { return &_fac; }
};

