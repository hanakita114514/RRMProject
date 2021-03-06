#pragma once
#include "Block.h"
#include <vector>
#include "MapRender.h"
#include "BackgroundRendar.h"

class EnemyFactory;
class Enemy;

typedef struct MAP_DAATA
{
	char* mapName;
	char* backGroundName;
}MapData;

enum class Stage
{
	stage1,
	stage2,
	stage3,
	stageMax
};

class MapManager
{
private:
	MapRender *map;
	BackgroundRendar _bg[(int)Stage::stageMax];
	EnemyFactory* _fac;
	Enemy* newEnemy;

	bool _mapErr;				//マップ読み込みエラー用フラグ
	bool _bgErr;				//背景読み込みエラー用フラグ
	bool createFlug;			//デバッグ用敵生成フラグ

	int _checkArray[MAP_ARRAY_SIZE_Y];
	int _checkNum;

	int _stageId;				//ステージID
	std::vector<Block*> _list[(int)Stage::stageMax];


	MapManager();
	MapManager(const MapManager&);
	MapManager& operator = (const MapManager&);

	std::vector<unsigned char> _m[(int)Stage::stageMax];
	std::vector<unsigned char> _enemy[(int)Stage::stageMax];
	FMFHEADER _header[(int)Stage::stageMax];

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
	void Finalize();

	EnemyFactory* GetEnemyFact() { return _fac; }
	std::vector<Block*>& GetList(int id) { return _list[id]; }
	MapRender* GetMap(int id) { return &map[id ]; }
	int GetStageId()			{ return _stageId; }

	bool StageSelect(int stageId);
	bool NextStage();

	void NormalizeArray(int idx);
	void EnemyCreate(int idx);
};

