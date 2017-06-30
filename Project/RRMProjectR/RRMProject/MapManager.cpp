#include "MapManager.h"
#include "BackgroundRendar.h"
#include "EnemyFactory.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "File.h"
#include "BlockManager.h"

const int MAP_CHIP_X_NUM = 8;
const int MAP_CHIP_X_NUM_EMPTY = 16;

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

	for (int i = 0; i < (int)Stage::stageMax; i++)
	{
		File* file = new File(_fileName[i].mapName);
		file->FileRead(&_header[i], sizeof(_header), 1);
		_m[i].resize(_header[i].dwHeight * _header[i].dwWidth);
		_enemy[i].resize(_header[i].dwHeight * _header[i].dwWidth);
		file->FileRead(&_m[i][0], _m[i].size(), 1, sizeof(_header[i]),&_enemy[i][0]);

		NormalizeArray(i);
	}
}

MapManager::~MapManager()
{
	delete map;
}

bool MapManager::Initialize()
{
	/*EnemyManager::Instance().Create(EnemyType::egg, Position(1214, 0));
	EnemyManager::Instance().Create(EnemyType::egg, Position(300, 0));	
	EnemyManager::Instance().Create(EnemyType::sushi, Position(640, 0));*/

	BlockManager::Instance().BlockInit(_m[_stageId], _header[_stageId].dwHeight, _header[_stageId].dwWidth);
	_list[_stageId] = BlockManager::Instance().GetBlockList();
	EnemyCreate(_stageId);

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
}

void MapManager::Draw(const Vector2& offset)
{
	_bg[_stageId].Draw();
}

bool
MapManager::StageSelect(int stageId)
{
	_stageId = stageId;

	if (_stageId >= (int)Stage::stageMax)
	{
		return false;
	}
	BlockManager::Instance().BlockInit(_m[_stageId], _header[stageId].dwHeight, _header[stageId].dwWidth);
	_list[_stageId] = BlockManager::Instance().GetBlockList();

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
	BlockManager::Instance().BlockInit(_m[_stageId], _header[_stageId].dwHeight, _header[_stageId].dwWidth);
	_list[_stageId] = BlockManager::Instance().GetBlockList();

	return true;
}
void MapManager::NormalizeArray(int idx)
{
	unsigned int  y, x;
	y = x = 0;

	for (y; y < _header[idx].dwHeight * _header[idx].dwWidth; ++y)
	{
		if (_m[idx][y] == '0')
		{
			continue;
		}
		_checkNum = (int)(_m[idx][y]) / MAP_CHIP_X_NUM_EMPTY;
		_m[idx][y] = (int)(_m[idx][y]) - _checkArray[_checkNum];
	}
}

void
MapManager::EnemyCreate(int idx)
{
	EnemyType type;
	Vector2 enemySize = {};

	for (int i = 0; i < _header[idx].dwHeight * _header[idx].dwWidth; ++i)
	{
		switch (_enemy[idx][i])
		{
		case (int)EnemyType::egg:
		{
			type = EnemyType::egg;
			enemySize = Vector2(64, 64);
			break;
		}
		case (int)EnemyType::mushroom:
		{
			type = EnemyType::mushroom;
			enemySize = Vector2(64, 64);
			break;
		}
		case (int)EnemyType::meat:
		{
			/*type = EnemyType::meat;
			enemySize = Vector2(64, 32);
			break;*/
			continue;
		}
		case (int)EnemyType::sushi:
		{
			type = EnemyType::sushi;
			enemySize = Vector2(64, 32);
			break;
		}
		case (int)EnemyType::tomato:
		{
			type = EnemyType::tomato;
			enemySize = Vector2(64, 64);
			break;
		}
		case (int)EnemyType::hamburger:
		{
			type = EnemyType::hamburger;
			enemySize = Vector2(64, 64);
			break;
		}
		default:
		{
			continue;
		}
		}
		EnemyManager::Instance().Create(type, Vector2(i % _header[idx].dwWidth  / 2 * enemySize.x,
							i / _header[idx].dwWidth / 2 * enemySize.y));
	}
}