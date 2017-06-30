#include "GameScene.h"
#include <RRMLib.h>
#include "MapManager.h"
#include "Block.h"
#include "Collision.h"
#include "EnemyManager.h"
#include "BulletManager.h"
#include "EnemyFactory.h"
#include "MapRender.h"
#include "Fade.h"
#include "EffectManager.h"
#include "BlockManager.h"
#include "SceneManager.h"

GameScene::GameScene() : _player(0,_camera, InputMode::pad), _camera(_player.GetRect().pos)
{
	_col = new Collision();
	EnemyManager::Instance();
	BulletManager::Instance();
	MapManager::Instance().Initialize();
	BlockManager::Instance();
	Fade::Instance().FadeOut(5.0f);
	_logoState = LogoIdx::GameStart;

	_camera.Init();
}

GameScene::GameScene(LogoIdx state, KeyData& keyData) : _player(0, _camera, keyData.mode), _camera(_player.GetRect().pos)
{
	_col = new Collision();
	EnemyManager::Instance();
	BulletManager::Instance();
	BlockManager::Instance();
	MapManager::Instance().Initialize();
	Fade::Instance().FadeOut(5.0f);
	_logoState = state;
	_sceneChangeFlag = false;

	_camera.Init();
}

GameScene::~GameScene()
{
	delete _col;
	BulletManager::Instance().Delete();
	EffectManager::Instance().Delete();
	BlockManager::Instance().Delete();
}

bool GameScene::Update()
{
	//更新--------------------------------------------------------------------

	if (!_sceneChangeFlag && Fade::Instance().IsFadeOutEnd())
	{
		if (Fade::Instance().IsWait())
		{
			_player.Update();
			MapManager::Instance().Update();
			EnemyManager::Instance().Update();
			BulletManager::Instance().Update();
			EffectManager::Instance().Update();
		}
		_camera.Update();

		//当たり判定
		ColProcess();
		EnemyManager::Instance().ScreenLimit(_camera);
	}

	//描画--------------------------------------------------------------------
	MapManager::Instance().Draw(_camera.GetOffset());
	BlockManager::Instance().Draw(_camera.GetOffset());
	EnemyManager::Instance().Draw(_camera.GetOffset());
	BulletManager::Instance().Draw(_camera.GetOffset());
	_player.Draw();
	EffectManager::Instance().Draw(_camera.GetOffset());
	_statusUI.Draw();
	_playerHP.Draw(_player.GetHP());

	StageClear();

	return true;
}

void
GameScene::PlayerColBlock()
{
	_player.SetHitGround(false);
	for (auto& block : BlockManager::Instance().GetBlockList())
	{
		Rect r = {};
		r = block->GetRect();

		if (block->GetBlockType() == BlockType::throughBlock1)
		{
			if (_col->IsHit(_player.GetRect(), *block, _player.GetVel()))
			{
				_player.Hit(block);
			}
		}
		else if (_col->IsHit(_player.GetRect(), r))
		{
			_player.Hit(block);
		}
	}
}

void 
GameScene::EnemyColBlock()
{
	MapRender* map = MapManager::Instance().GetMap(0);
	bool hitFlag = false;

	for (auto& enemy : EnemyManager::Instance().GetEnemyList())
	{
		for (auto& block : BlockManager::Instance().GetBlockList())
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
		segmentHit = _col->LineCross(_player.GetRect(), _player.GetVel(), e->GetRect(), e->GetVel());
		if (segmentHit || hitFlag)
		{
			_player.Hit(e);
			break;
		}
	}

	//ヒットボックスとの当たり判定
	for (auto& e : EnemyManager::Instance().GetEnemyList())
	{
		if (e->IsDead())
		{
			continue;
		}

		//攻撃判定
		for (auto& a : _player.GetAttackBoxes())
		{
			if (_player.GetHitProtect().IsAlreadyHit(e))
			{
				continue;
			}
			if (_col->IsHit(a.rc, e->GetRect()))
			{
				//ヒット
				_player.GetHitProtect().Hit(e);
				e->Damage(a.power, a.vec);
				e->HitStop(a.hitstop);
				_player.HitStop(a.hitstop);
				_camera.Quake(Vector2(10, 5));
			}
		}

		//喰らい判定
		for (auto& d : _player.GetDamageBoxes())
		{
			if (_col->IsHit(d.rc, e->GetRect()))
			{
				//ヒット
			}
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
			_player.Hit(b);
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
		for (auto& block : BlockManager::Instance().GetBlockList())
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

void GameScene::StageClear()
{
	if (Fade::Instance().IsFadeInEnd())
	{
		_sceneChangeFlag = true;
	}

	if (EnemyManager::Instance().EnemyEradication() && Fade::Instance().IsWait())
	{
		Fade::Instance().FadeIn(10.0);
	}

//	RRMLib::DrawFormatString(0, 0, 0xffffffff, "GameScene");

	if (_sceneChangeFlag)
	{
		SceneManager::Instance().LogoState(_logoState);
		SceneManager::Instance().ChangeScene(SceneType::result);
	}
}