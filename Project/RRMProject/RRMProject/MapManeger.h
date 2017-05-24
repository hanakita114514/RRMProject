#pragma once
#include "Block.h"
#include <vector>

class MapRendar;
class BackgroundRendar;
class EnemyFactory;
class EnemyManager;
class Enemy;

class MapManeger
{
private:
	MapRendar* _map;
	BackgroundRendar* _bg;
	EnemyFactory* _fac;
	EnemyManager* _enemy;
	Enemy* newEnemy;

	bool _mapErr;				//マップ読み込みエラー用フラグ
	bool _bgErr;				//背景読み込みエラー用フラグ
	bool createFlug;			//デバッグ用敵生成フラグ
	std::vector<Block> _list;
public:
	MapManeger();
	~MapManeger();

	bool Initialize();
	void Draw();
	void Update();
	void Finalize();

	EnemyFactory* GetEnemyFact() { return _fac; }
	std::vector<Block> GetList() { return _list; }
	MapRendar* GetMap() { return _map; }
};

