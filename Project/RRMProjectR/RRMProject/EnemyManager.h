#pragma once
#include "Enemy.h"
#include <vector>
#include "EnemyFactory.h"

class EnemyManager
{
private:
	EnemyManager();
	EnemyManager(const EnemyManager&);
	EnemyManager& operator = (const EnemyManager&);

	EnemyFactory _fac;
	std::vector<Enemy*> _enemyList;

public:
	~EnemyManager();

	static EnemyManager& Instance()
	{
		static EnemyManager instance;
		return instance;
	}

	void Update();						//XV
	void Draw(const Vector2& offset);	//•`‰æ
	void ScreenLimit(Camera& camera);

	void Create(const EnemyType& et, const Position& pos);
	void Delete();

	std::vector<Enemy*>& GetEnemyList() { return _enemyList; }

	bool EnemyEradication();
};

