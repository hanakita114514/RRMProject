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

MapManager::MapManager()
{
	//ファイル名を各クラスに渡しておく
	_map = new MapRendar("Resource/data/map2.fmf");
	_bg = new BackgroundRendar("Resource/img/BackGround/mori.jpg");
	createFlug = false;

	EnemyManager::Instance().Create(EnemyType::egg, Position(500, 0));
	EnemyManager::Instance().Create(EnemyType::egg, Position(300,0));
	EnemyManager::Instance().Create(EnemyType::egg, Position(1214, 0));

}

MapManager::~MapManager()
{
	delete _map;
	delete _bg;

	Delete();
}

bool MapManager::Initialize()
{
	_mapErr = _map->MapLoad();
	_bgErr = _bg->Initialize();

	if (_mapErr != true || _bgErr != true)	//マップもしくは背景で失敗したか？
	{
		return false;
	}

	return true;
}

void MapManager::Finalize()
{
	delete(_map);
	delete(_bg);
}

void MapManager::Update()
{

	_list = _map->GetBlockList();
}

void MapManager::Draw(const Vector2& offset)
{
	_bg->Draw();
	_map->MapDraw(offset);
}

void 
MapManager::Delete()
{
	auto itr = _list.begin();

	for (; itr != _list.end();)
	{
		delete (*itr);
		itr = _list.erase(itr);
	}
}
