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

	void Update();						//更新

	//死んだ敵を消す更新
	//戻り値 削除した敵の数が返る
	int DeleteUpdate();

	void Draw(const Vector2& offset);	//描画
	void ScreenLimit(Camera& camera);

	void Create(const EnemyType& et, const Position& pos);
	void Delete();

	std::vector<Enemy*>& GetEnemyList() { return _enemyList; }

	bool EnemyEradication();
};

