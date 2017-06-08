#pragma once
#include "Block.h"
#include <vector>

const int STAGE_ID_MAX = 4;

class MapRendar;
class BackgroundRendar;
class EnemyFactory;
class Enemy;

typedef struct MAP_DAATA
{
	char* mapName;
	char* backGroundName;
}MapData;


class MapManager
{
private:
	MapRendar* _map[STAGE_ID_MAX];
	BackgroundRendar* _bg[STAGE_ID_MAX];
	EnemyFactory* _fac;
	Enemy* newEnemy;

	bool _mapErr;				//マップ読み込みエラー用フラグ
	bool _bgErr;				//背景読み込みエラー用フラグ
	bool createFlug;			//デバッグ用敵生成フラグ

	int _stageId;				//ステージID
	std::vector<Block*> _list;


	MapManager();
	MapManager(const MapManager&);
	MapManager& operator = (const MapManager&);


public:
	~MapManager();

	static MapManager& Instance()
	{
		static MapManager instance;
		return instance;
	}

	bool Initialize();
	void Update();
	void Draw(const Vector2& offset);
	void Delete();
	void Finalize();

	EnemyFactory* GetEnemyFact() { return _fac; }
	std::vector<Block*>& GetList() { return _list; }
	MapRendar* GetMap(int id) { return _map[id ]; }
	int GetStageId()			{ return _stageId; }

	MapRendar* StageSelect(int stageId);
};

