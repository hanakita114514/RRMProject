#pragma once
#include "Block.h"
#include <vector>
#include "MapRendar.h"
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
	MapRendar _map[(int)Stage::stageMax];
	BackgroundRendar _bg[(int)Stage::stageMax];
	EnemyFactory* _fac;
	Enemy* newEnemy;

	bool _mapErr;				//�}�b�v�ǂݍ��݃G���[�p�t���O
	bool _bgErr;				//�w�i�ǂݍ��݃G���[�p�t���O
	bool createFlug;			//�f�o�b�O�p�G�����t���O

	int _stageId;				//�X�e�[�WID
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
	MapRendar* GetMap(int id) { return &_map[id ]; }
	int GetStageId()			{ return _stageId; }

	bool StageSelect(int stageId);
	bool NextStage();
};

