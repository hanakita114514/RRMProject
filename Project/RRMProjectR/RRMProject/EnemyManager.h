#pragma once
#include "Enemy.h"
#include <vector>
#include "EnemyFactory.h"
#include "Camera.h"

class EnemyManager
{
private:
	EnemyManager();
	EnemyManager(const EnemyManager&);
	EnemyManager& operator = (const EnemyManager&);

	EnemyFactory _fac;
	std::vector<Enemy*> _enemyList;

	std::vector<Enemy*> _reservation;	//—\–ñƒŠƒXƒg
public:
	~EnemyManager();

	static EnemyManager& Instance()
	{
		static EnemyManager instance;
		return instance;
	}

	void Update();						//XV

	//€‚ñ‚¾“G‚ğÁ‚·XV
	//–ß‚è’l íœ‚µ‚½“G‚Ì”‚ª•Ô‚é
	int DeleteUpdate();

	void Draw(const Vector2& offset);	//•`‰æ
	void ScreenLimit(Camera& camera);

	void Create(const EnemyType& et, const Position& pos);
	void Create(const EnemyType& et, const Position& pos, const Position& playerPos, Camera& camera);

	void AddList(const EnemyType& et, const Position& pos);
	void Delete();

	std::vector<Enemy*>& GetEnemyList() { return _enemyList; }

	bool EnemyEradication();
};

