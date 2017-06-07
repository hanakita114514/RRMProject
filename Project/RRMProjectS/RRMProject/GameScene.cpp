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
#include "EffectManager.h"

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
	EffectManager::Instance().Update();
	_camera.Update();

	//“–‚½‚è”»’è
	ColProcess();

	//•`‰æ--------------------------------------------------------------------
	MapManager::Instance().Draw(_camera.GetOffset());
	EnemyManager::Instance().Draw(_camera.GetOffset());
	BulletManager::Instance().Draw(_camera.GetOffset());
	_player.Draw();
	EffectManager::Instance().Draw(_camera.GetOffset());

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
	bool hitFlag = false;

	for (auto& enemy : EnemyManager::Instance().GetEnemyList())
	{
		for (auto& block : MapManager::Instance().GetList())
		{
			Rect r = {};
			r = block->GetRect();
			hitFlag = _col->IsHit(enemy->GetRect(), r);
			if (hitFlag == true)
			{
				enemy->Hit(block);
				break;
			}
		}
		if (hitFlag == false)
		{
			enemy->SetHitGround(false);
		}

	}
}

void GameScene::PlayerColEnemy()
{
	bool hitFlag = false;
	bool segmentHit = false;
	for (auto& e : EnemyManager::Instance().GetEnemyList())
	{
		if (e->IsDead())
		{
			continue;
		}
		segmentHit = _col->LineCross(_player.GetRect(),_player.GetVel(), e->GetRect(),e->GetVel());
		//hitFlag = _col->IsHit(_player.GetRect(), e->GetRect());
		if (segmentHit || hitFlag)
		{
			_player.Hit(e);
			//e->Hit(&_player);

			break;
		}
	}
}

void
GameScene::BulletColPlayer()
{
	bool hitFlag = false;
	bool segmentHit = false;

	for (auto& b : BulletManager::Instance().GetBulletList())
	{
		if (!b->IsAlive())
		{
			continue;
		}

		hitFlag = _col->IsHit(_player.GetRect(), b->GetCircle());
		if ((hitFlag || segmentHit) && (_player.GetObjType() != b->GetObjType()))
		{
			b->Hit(&_player);
		}

	}
}

void
GameScene::BulletColBlock()
{
	bool hitFlag = false;

	for (auto& bullet : BulletManager::Instance().GetBulletList())
	{
		if (!bullet->IsAlive())
		{
			continue;
		}
		if (bullet->GetObjType() == ObjectType::enemy)
		{
			continue;
		}
		for (auto& block : MapManager::Instance().GetList())
		{
			hitFlag = _col->IsHit(block->GetRect(), bullet->GetCircle());
			if (hitFlag == true && (block->GetObjType() != bullet->GetObjType()))
			{
				(bullet)->Hit(block);
				bullet->Finalize();
				break;
			}
		}
	}
}

void
GameScene::BulletColEnemy()
{
	bool hitFlag = false;


	for (auto& bullet : BulletManager::Instance().GetBulletList())
	{
		if (!bullet->IsAlive())
		{
			continue;
		}
		for (auto& enemy : EnemyManager::Instance().GetEnemyList())
		{
			if (enemy->IsDead())
			{
				continue;
			}
			hitFlag = _col->IsHit(enemy->GetRect(), bullet->GetCircle());
			if (hitFlag == true && (enemy->GetObjType() != bullet->GetObjType()))
			{
				(bullet)->Hit(enemy);
				enemy->Hit(bullet);
				bullet->Finalize();
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