#include "MapManager.h"
#include "BackgroundRendar.h"
#include "MapRendar.h"
#include "EnemyFactory.h"
#include "EnemyManager.h"
#include "GameMain.h"
#include "Enemy.h"
#include "Collision.h"
#include "Player.h"
#include "EnemyManager.h"

MapData _fileName[(int)Stage::stageMax] =
{
	{"Resource/data/map1.fmf","Resource/img/BackGround/mori.jpg"},
	{ "Resource/data/map2.fmf","Resource/img/BackGround/mori.jpg" },
	{ "Resource/data/map1.fmf","Resource/img/BackGround/mori.jpg" },
	{ "Resource/data/map2.fmf","Resource/img/BackGround/mori.jpg" }
};

MapManager::MapManager()
{
	//ファイル名を各クラスに渡しておく
	for (int i = 0; i < (int)Stage::stageMax; i++)
	{
		_map[i] = new MapRendar(_fileName[i].mapName);
		_bg[i] = new BackgroundRendar(_fileName[i].backGroundName);
	}


	_stageId = 0;
}

MapManager::~MapManager()
{
	Delete();

	delete[] _map;
	delete[] _bg;
}

bool MapManager::Initialize()
{
	_mapErr = _map[_stageId]->MapLoad();
	_bgErr = _bg[_stageId]->Initialize();
	EnemyManager::Instance().Create(EnemyType::egg, Position(1214, 0));


	if (!_mapErr|| !_bgErr)	//マップもしくは背景で失敗したか？
	{
		return false;
	}

	return true;
}

void MapManager::Finalize()
{
		delete[] _map;
		delete[] _bg;
}

void MapManager::Update()
{
	_list = _map[_stageId]->GetBlockList();
}

void MapManager::Draw(const Vector2& offset)
{
	_bg[_stageId]->Draw();
	_map[_stageId]->MapDraw(offset);
}

void 
MapManager::Delete()
{
	auto itr = _list.begin();

	for (; itr != _list.end();)
	{
		delete (*itr);
		*itr = nullptr;
		itr = _list.erase(itr);
	}
}

bool
MapManager::StageSelect(int stageId)
{
	_stageId = stageId;

	if (_stageId >= (int)Stage::stageMax)
	{
		return false;
	}
	 _map[_stageId];

	 return true;
}

bool
MapManager::NextStage()
{
	_stageId++;

	if (_stageId >= (int)Stage::stageMax)
	{
		return false;
	}
	_map[_stageId];

	return true;
}
