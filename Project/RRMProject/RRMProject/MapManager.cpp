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
}

MapManager::~MapManager()
{

}

bool MapManager::Initialize()
{
	_mapErr = _map->MapLoad();
	_bgErr = _bg->Initialize();

	if (_mapErr != true || _bgErr != true)	//マップもしくは背景で失敗したか？
	{
		return false;
	}

	
	_fac = EnemyManager::Instance().GetEnemyFac();

	Enemy* enemy = nullptr;

	return true;
}

void MapManager::Finalize()
{
	delete(_map);
	delete(_bg);
}

void MapManager::Update()
{
	if (createFlug != true)
	{
		newEnemy = _fac->Create(EnemyType::egg);
		EnemyManager::Instance().Push(newEnemy);
		createFlug = true;
	}

	_list = _map->GetBlockList();
}

void MapManager::Draw()
{
	_bg->Draw();
	_map->MapDraw();
}
