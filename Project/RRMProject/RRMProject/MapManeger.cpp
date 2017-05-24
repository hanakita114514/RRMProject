#include "MapManeger.h"
#include "BackgroundRendar.h"
#include "MapRendar.h"
#include "EnemyFactory.h"
#include "EnemyManager.h"
#include "GameMain.h"
#include "Enemy.h"
#include "Collision.h"
#include "Player.h"

MapManeger::MapManeger()
{
	//ファイル名を各クラスに渡しておく
	_map = new MapRendar("Resource/data/map2.fmf");
	_bg = new BackgroundRendar("Resource/img/BackGround/mori.jpg");
	createFlug = false;
}

MapManeger::~MapManeger()
{

}

bool MapManeger::Initialize()
{
	_mapErr = _map->MapLoad();
	_bgErr = _bg->Initialize();

	if (_mapErr != true || _bgErr != true)	//マップもしくは背景で失敗したか？
	{
		return false;
	}

	EnemyManager* e = GameMain::Instance().GetEnemy();
	_fac = e->GetEnemyFac();

	Enemy* enemy = nullptr;

	return true;
}

void MapManeger::Finalize()
{
	delete(_map);
	delete(_bg);
}

void MapManeger::Update()
{
	_enemy = GameMain::Instance().GetEnemy();
	if (createFlug != true)
	{
		newEnemy = _fac->Create(EnemyType::egg);
		_enemy->Push(newEnemy);
		createFlug = true;
	}

	_list = _map->GetBlockList();
}

void MapManeger::Draw()
{
	_bg->Draw();
	_map->MapDraw();
}
