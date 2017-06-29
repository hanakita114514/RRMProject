#include "MapManager.h"
#include "BackgroundRendar.h"
#include "EnemyFactory.h"
#include "EnemyManager.h"
#include "GameMain.h"
#include "Enemy.h"
#include "Collision.h"
#include "Player.h"
#include "EnemyManager.h"
#include "File.h"
#include "BlockManager.h"

const int MAP_CHIP_X_NUM = 8;

MapData _fileName[(int)Stage::stageMax] =
{
	{ "Resource/data/map/map1.fmf","Resource/img/BackGround/mori.jpg" },
	{ "Resource/data/map/map2.fmf","Resource/img/BackGround/mori.jpg" },
	{ "Resource/data/map/map3.fmf","Resource/img/BackGround/mori.jpg" },
	{ "Resource/data/map/map4.fmf","Resource/img/BackGround/mori.jpg" }
};

MapManager::MapManager()
{
	//ファイル名を各クラスに渡しておく
	for (int i = 0; i < (int)Stage::stageMax; i++)
	{
		//_map[i].Initialize(_fileName[i].mapName);
		_bgErr = _bg[i].Initialize(_fileName[i].backGroundName);
	}

	map = new MapRender();

	_stageId = 0;

	for (int i = 0; i < MAP_ARRAY_SIZE_Y; i++)
	{
		_checkArray[i] = MAP_IMAGE_X_NUM * i;
	}
}

MapManager::~MapManager()
{
}

bool MapManager::Initialize()
{
	//_mapErr = _map[1].MapLoad();
	EnemyManager::Instance().Create(EnemyType::egg, Position(1214, 0));
	EnemyManager::Instance().Create(EnemyType::egg, Position(300, 0));

	_mapErr = true;

	for (int i = 0; i < (int)Stage::stageMax; i++)
	{
		File* file = new File(_fileName[i].mapName);
		file->FileRead(&_header, sizeof(_header), 1);
		_m[i].resize(_header.dwHeight * _header.dwWidth);
		file->FileRead(&_m[i][0], _m[i].size(), 1,sizeof(_header));

		NormalizeArray(i);

		file->Finalize();
	}

	BlockManager::Instance().BlockInit(_m[_stageId], _header.dwHeight, _header.dwWidth);
	_list[_stageId] = BlockManager::Instance().GetBlockList();

	if (!_mapErr|| !_bgErr)	//マップもしくは背景で失敗したか？
	{
		return false;
	}
	return true;
}

void MapManager::Finalize()
{

}

void MapManager::Update()
{
	//_list = _map[1].GetBlockList();
}

void MapManager::Draw(const Vector2& offset)
{
	_bg[_stageId].Draw();
	map->MapDraw(_list[_stageId], offset);
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
void MapManager::NormalizeArray(int idx)
{
	unsigned int  y, x;
	y = x = 0;

	for (y; y < _header.dwHeight * _header.dwWidth; ++y)
	{
		_checkNum = _m[idx][y] / MAP_CHIP_X_NUM;
		_m[idx][y] = (int)(_m[idx][y] - _checkArray[_checkNum]);
	}
}

