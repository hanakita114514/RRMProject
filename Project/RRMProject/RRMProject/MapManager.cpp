#include "MapManager.h"
#include "BackgroundRendar.h"
#include "MapRendar.h"
#include "EnemyFactory.h"
#include "EnemyManager.h"
#include "GameMain.h"
#include "Enemy.h"
#include "Collision.h"
#include "Player.h"

MapManager::MapManager()
{
	//�t�@�C�������e�N���X�ɓn���Ă���
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

	if (_mapErr != true || _bgErr != true)	//�}�b�v�������͔w�i�Ŏ��s�������H
	{
		return false;
	}

	EnemyManager* e = GameMain::Instance().GetEnemy();
	_fac = e->GetEnemyFac();

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
	_enemy = GameMain::Instance().GetEnemy();
	if (createFlug != true)
	{
		newEnemy = _fac->Create(EnemyType::egg);
		_enemy->Push(newEnemy);
		createFlug = true;
	}

	_list = _map->GetBlockList();
}

void MapManager::Draw()
{
	_bg->Draw();
	_map->MapDraw();
}
