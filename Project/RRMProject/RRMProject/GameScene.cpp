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
	//çXêV--------------------------------------------------------------------

	_player.Update();
	MapManager::Instance().Update();
	EnemyManager::Instance().Update();
	BulletManager::Instance().Update();
	_camera.Update();

	//ìñÇΩÇËîªíË
	ColProcess();

	//ï`âÊ--------------------------------------------------------------------
	MapManager::Instance().Draw(_camera.GetOffset());
	_player.Draw();
	EnemyManager::Instance().Draw(_camera.GetOffset());
	BulletManager::Instance().Draw();

	DxLib::DrawFormatString(0, 0, 0xffffffff, "GameScene");

	return true;
}

void
GameScene::PlayerColBlock()
{
	bool hitFlug = false;
	std::vector<Block*>& blockList = MapManager::Instance().GetList();
	for (auto& block : blockList)
	{
		Rect r = {};
		r = block->GetRect();
		hitFlug = _col->IsHit(_player.GetRect(), _player.GetVel(), r);
		if (hitFlug == true)
		{
			_player.Hit(block);
			break;
		}
	}
	if (hitFlug == false)
	{
		_player.SetHitGround(false);
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
			hitFlug = _col->IsHit(enemy->GetRect(),enemy->GetVel(), r);
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
		hitFlug = _col->IsHit(_player.GetRect(),_player.GetVel(), e->GetRect());
		if (hitFlug == true)
		{
			//_col->PushBack(_player.GetRect(), *e);
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

//void
//GameScene::CreateColBox()
//{
//	Rect wr = {};
//
//	MapRendar* map = MapManager::Instance().GetMap();
//	std::vector<Block*>& b = map->GetBlockList();
//	std::vector<Block*>::iterator itr = b.begin();
//	Rect r = {};
//	r = (*itr)->GetRect();
//
//	for (itr; itr != b.end();)
//	{
//		if (itr == b.end() - 1)
//		{
//			Block* block = new Block();
//			r.w += (*itr)->GetRect().w;
//			block->SetPos(r);
//			_colBlock.push_back(block);
//			break;
//		}
//		else if ((itr + 1)->GetRect().pos.x - itr->GetRect().pos.x == itr->GetRect().w)
//		{
//			r.w += itr->GetRect().w;
//			++itr;
//		}
//		else
//		{
//			Block* block = new Block();
//			block->SetPos(r);
//			_colBlock.push_back(block);
//			++itr;
//			r = itr->GetRect();
//		}
//	}
//	int i = 0;
//}

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