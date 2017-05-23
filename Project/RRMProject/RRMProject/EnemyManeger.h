#pragma once
#include "Enemy.h"
#include <vector>

class EnemyFactory;

class EnemyManeger
{
private:
	std::vector<Enemy*> _enemyList;
	EnemyFactory* _fac;
public:
	EnemyManeger();
	~EnemyManeger();

	void Update();						//XV
	void Draw();						//•`‰æ
	void Push(Enemy* enemy);
	void Delete();

	EnemyFactory* GetEnemyFac() { return _fac; }
};

