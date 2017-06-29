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
	stage4,
	stageMax
};

class MapManager
{
private:
	MapRender _map[(int)Stage::stageMax],*map;
	BackgroundRendar _bg[(int)Stage::stageMax];
	EnemyFactory* _fac;
	Enemy* newEnemy;

	bool _mapErr;				//�}�b�v�ǂݍ��݃G���[�p�t���O
	bool _bgErr;				//�w�i�ǂݍ��݃G���[�p�t���O
	bool createFlug;			//�f�o�b�O�p�G�����t���O

	int _checkArray[MAP_ARRAY_SIZE_Y];
	int _checkNum;

	int _stageId;				//�X�e�[�WID
	std::vector<Block*> _list[(int)Stage::stageMax];


	MapManager();
	MapManager(const MapManager&);
	MapManager& operator = (const MapManager&);

	std::vector<unsigned char> _m[(int)Stage::stageMax];
	FMFHEADER _header;

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
	MapRender* GetMap(int id) { return &_map[id ]; }
	int GetStageId()			{ return _stageId; }

	bool StageSelect(int stageId);
	bool NextStage();

	void NormalizeArray(int idx);
};

