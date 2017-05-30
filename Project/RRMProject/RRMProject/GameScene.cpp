#include "GameScene.h"
#include <DxLib.h>
#include "MapManager.h"
#include "Block.h"
#include "Collision.h"
#include "EnemyManager.h"
#include "BulletManager.h"
#include "EnemyFactory.h"
#include "MapRendar.h"
#include "Fade.h"

GameScene::GameScene() : _player(0,_camera), _camera(_player.GetRect().pos)
{
	_col = new Collision();
	EnemyManager::Instance();
	BulletManager::Instance();
	MapManager::Instance().Initialize();
	Fade::Instance().FadeOut(5.0f);

	_camera.Init();
}


GameScene::~GameScene()
{
	delete _col;
}

bool GameScene::Update()
{
	//XV--------------------------------------------------------------------

	_player.Update();
	MapManager::Instance().Update();
	EnemyManager::Instance().Update();
	BulletManager::Instance().Update();
	_camera.Update();

	//“–‚½‚è”»’è
	ColProcess();

	//•`‰æ--------------------------------------------------------------------
	MapManager::Instance().Draw(_camera.GetOffset());
	_player.Draw();
	EnemyManager::Instance().Draw(_camera.GetOffset());
	BulletManager::Instance().Draw(_camera.GetOffset());

	DxLib::DrawFormatString(0, 0, 0xffffffff, "GameScene");

	return true;
}

void
GameScene::PlayerColBlock()
{
	_player.SetHitGround(false);
	for (auto& block : MapManager::Instance().GetList())
	{
		Rect r = {};
		r = block->GetRect();
		if (_col->IsHit(_player.GetRect(), r))
		{
			_player.Hit(block);
		}
	}
}

void 
GameScene::EnemyColBlock()
{
	MapRendar* map = MapManager::Instance().GetMap();
	bool hitFlug = false;

	for (auto& enemy : EnemyManager::Instance().GetEnemyList())
	{
		for (auto& block : MapManager::Instance().GetList())
		{
			Rect r = {};
			r = block->GetRect();
			hitFlug = _col->IsHit(enemy->GetRect(), r);
			if (hitFlug == true)
			{
				enemy->Hit(block);
				break;
			}
		}
		if (hitFlug == false)
		{
			enemy->SetHitGround(false);
		}

	}
}

void GameScene::PlayerColEnemy()
{
	bool hitFlug;

	for (auto& e : EnemyManager::Instance().GetEnemyList())
	{
		hitFlug = _col->LineCross(_player.GetRect(),_player.GetVel(), e->GetRect(),e->GetVel());
		if (hitFlug == true)
		{
			_player.Hit(e);
			e->Hit(&_player);

			break;
		}
	}
}

void
GameScene::BulletColPlayer()
{
	bool hitFlug = false;


	for (auto& b : BulletManager::Instance().GetBulletList())
	{
		hitFlug = _col->IsHit(_player.GetRect(), b->GetCircle());
		if (hitFlug == true && (_player.GetObjType() != b->GetObjType()))
		{
			b->Hit(&_player);
			break;
		}

	}
}

void
GameScene::BulletColBlock()
{
	bool hitFlug = false;

	for (auto& bullet : BulletManager::Instance().GetBulletList())
	{
		for (auto& block : MapManager::Instance().GetList())
		{
			hitFlug = _col->IsHit(block->GetRect(), bullet->GetCircle());
			if (hitFlug == true && (block->GetObjType() != bullet->GetObjType()))
			{
				(bullet)->Hit(block);
				break;
			}
		}
	}
}

void
GameScene::BulletColEnemy()
{
	bool hitFlug = false;


	for (auto& bullet : BulletManager::Instance().GetBulletList())
	{
		for (auto& enemy : EnemyManager::Instance().GetEnemyList())
		{
			hitFlug = _col->IsHit(enemy->GetRect(), bullet->GetCircle());
			if (hitFlug == true && (enemy->GetObjType() != bullet->GetObjType()))
			{
				(bullet)->Hit(enemy);
				enemy->Hit(bullet);
				break;
			}
		}
	}

}


void 
GameScene::ColProcess()
{
	PlayerColBlock();
	EnemyColBlock();
	PlayerColEnemy();
	BulletColBlock();
	BulletColPlayer();
	BulletColEnemy();
}