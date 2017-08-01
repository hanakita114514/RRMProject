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
#include "GameTime.h"
#include "InputFactory.h"
#include "Result.h"


GameScene::GameScene() : _player(0,_camera, InputMode::keyboard), _camera(_player.GetRect().pos), _time(Position(0, 0), 40.f)
{
	_col = new Collision();
	EnemyManager::Instance();
	BulletManager::Instance();
	MapManager::Instance().Initialize();
	BlockManager::Instance();
	Fade::Instance().FadeOut(5.0f);
	_logoState = LogoIdx::GameStart;

	_update[SceneState::start] = &GameScene::StartUpdate;
	_update[SceneState::game] = &GameScene::GameUpdate;
	_update[SceneState::end] = &GameScene::EndUpdate;
	_update[SceneState::result] = &GameScene::ResultUpdate;

	_state = SceneState::start;

	_endFrame = 0;

	_camera.Init();

	_input = InputFactory::Create(InputMode::pad, 0);
	_result = new  Result(_score, _player.GetHitPoint(), _time, _player.GetCombo());

}

GameScene::GameScene(LogoIdx state, KeyData& keyData) : _player(0, _camera, InputMode::pad), _camera(_player.GetRect().pos),
_time(Position(720, 40.0f), 40.f)
{
	_col = new Collision();
	EnemyManager::Instance();
	BulletManager::Instance();
	BlockManager::Instance();
	MapManager::Instance().Initialize();
	Fade::Instance().FadeOut(5.0f);
	_logoState = state;
	_sceneChangeFlag = false;

	_update[SceneState::start] = &GameScene::StartUpdate;
	_update[SceneState::game] = &GameScene::GameUpdate;
	_update[SceneState::end] = &GameScene::EndUpdate;
	_update[SceneState::result] = &GameScene::ResultUpdate;
	_state = SceneState::start;

	_endFrame = 0;

	_camera.Init();

	_input = InputFactory::Create(InputMode::pad, 0);

	_result = new Result(_score, _player.GetHitPoint(), _time, _player.GetCombo());


	if (MapManager::Instance().GetStageId() == 2)
	{
		EnemyManager::Instance().Create(EnemyType::hamburger, Position(100, 300), _player.GetRect().pos, _camera);
	}
}

GameScene::~GameScene()
{
	delete _col;
	BulletManager::Instance().Delete();
	EffectManager::Instance().Delete();
	BlockManager::Instance().Delete();
}

void
GameScene::StartUpdate()
{
	if (!_sceneChangeFlag && Fade::Instance().IsFadeOutEnd())
	{
		if (Fade::Instance().IsWait())
		{
			_state = SceneState::game;
			_time.Start();
		}
	}
}

void
GameScene::GameUpdate()
{
	//XV--------------------------------------------------------------------
	_player.Update();
	_player.SlowDownUpdate();
	MapManager::Instance().Update();
	EnemyManager::Instance().Update();
	BulletManager::Instance().Update();
	EffectManager::Instance().Update();
	_foodManager.Update();
	_player.GetCombo().CollectON(_foodManager, _player.GetRect().pos);

	int deadEnemy = EnemyManager::Instance().DeleteUpdate();
	_score.Add(deadEnemy * _player.GetCombo().GetComboNum() * 100);

	_camera.Update();

		//“–‚½‚è”»’è
	ColProcess();
	EnemyManager::Instance().ScreenLimit(_camera);

	//•`‰æ--------------------------------------------------------------------
	MapManager::Instance().Draw(_camera.GetOffset());
	BlockManager::Instance().Draw(_camera.GetOffset());
	EnemyManager::Instance().Draw(_camera.GetOffset());
	BulletManager::Instance().Draw(_camera.GetOffset());
	_player.Draw();
	EffectManager::Instance().Draw(_camera.GetOffset());
	_foodManager.Draw(_camera.GetOffset());
	_statusUI.Draw();
	_time.Draw();
	_player.UIDraw();
	_infoUI.Draw();
	
	_score.Draw();


	if (EnemyManager::Instance().EnemyEradication())
	{
		GameTime::Instance().SetTimeScale(0.5f);
		_state = SceneState::end;
	}

}

void
GameScene::EndUpdate()
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
	EnemyManager::Instance().ScreenLimit(_camera);

	//•`‰æ--------------------------------------------------------------------
	MapManager::Instance().Draw(_camera.GetOffset());
	BlockManager::Instance().Draw(_camera.GetOffset());
	EnemyManager::Instance().Draw(_camera.GetOffset());
	BulletManager::Instance().Draw(_camera.GetOffset());
	_player.Draw();
	EffectManager::Instance().Draw(_camera.GetOffset());
	_statusUI.Draw();
	_time.Draw();
	_player.UIDraw();
	_infoUI.Draw();
	_score.Draw();

	if (_endFrame >= 90)
	{
		_endFrame = 0;
		GameTime::Instance().SetTimeScale(1.0f);
		_state = SceneState::result;
		_time.Stop();
	}

	++_endFrame;

}

void 
GameScene::ResultUpdate()
{
	//•`‰æ--------------------------------------------------------------------
	MapManager::Instance().Draw(_camera.GetOffset());
	BlockManager::Instance().Draw(_camera.GetOffset());
	EnemyManager::Instance().Draw(_camera.GetOffset());
	BulletManager::Instance().Draw(_camera.GetOffset());
	_player.Draw();
	EffectManager::Instance().Draw(_camera.GetOffset());

	_result->Update();

	if (_result->IsEnd() && _input->Start())
	{
		StageClear();
	}
}

bool 
GameScene::Update()
{
	_input->Update();
	(this->*_update[_state])();

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
	bool hitFlag = false;


	for (auto& enemy : EnemyManager::Instance().GetEnemyList())
	{
		enemy->SetHitGround(false);

		for (auto& block : BlockManager::Instance().GetBlockList())
		{
			Rect r = {};
			r = block->GetRect();
			hitFlag = _col->IsHit(enemy->GetRect(), r);
			if (hitFlag == true)
			{
				enemy->Hit(block);
			}
		}
	}

	for (auto& enemy : EnemyManager::Instance().GetEnemyList())
	{
		if (enemy->GetHitBox() == nullptr)
		{
			continue;
		}
		enemy->SetFootHit(false);
		for (auto& block : BlockManager::Instance().GetBlockList())
		{
			//’n–Ê’T‚µ
			for (auto& footRc : enemy->GetHitBox()->GetFootRects())
			{
				if (_col->IsHit(footRc, block->GetRect()))
				{
					enemy->SetFootHit(true);
					break;
				}
			}
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

	//ƒqƒbƒgƒ{ƒbƒNƒX‚Æ‚Ì“–‚½‚è”»’è
	for (auto& e : EnemyManager::Instance().GetEnemyList())
	{
		if (e->IsDead())
		{
			continue;
		}

		//UŒ‚”»’è
		for (auto& a : _player.GetAttackBoxes())
		{
			if (_player.GetHitProtect().IsAlreadyHit(e))
			{
				continue;
			}
			if (_col->IsHit(a.rc, e->GetRect()))
			{
				//ƒqƒbƒg
				_player.GetHitProtect().Hit(e);
				_player.GetCombo().Hit();
				e->Damage(a.power, a.vec);
				e->HitStop(a.hitstop);
				_player.HitStop(a.hitstop);
				_camera.Quake(Vector2(10, 5));
				EffectManager::Instance().Create(EffectType::slash2,e->GetRect().Center(), Vector2(0.5f, 0.5f), 0.2f);

				for(int i = 0; i < _player.GetCombo().GetComboNum(); ++i)
				{
					_foodManager.RandomCreate(e->GetRect().Center());
				}
			}
		}

		//‹ò‚ç‚¢”»’è
		for (auto& d : _player.GetDamageBoxes())
		{
			if (_col->IsHit(d.rc, e->GetRect()))
			{
				//ƒqƒbƒg
			}
		}
	}

	for (auto& enemy : EnemyManager::Instance().GetEnemyList())
	{
		if (enemy->GetHitBox() == nullptr)
		{
			continue;
		}
		//ƒvƒŒƒCƒ„[’T‚µ
		for (auto& searchRc : enemy->GetHitBox()->GetSearchRects())
		{
			enemy->SearchFailed();
			if (_col->IsHit(searchRc, _player.GetRect()))
			{
				enemy->SearchHit(_player.GetRect().pos);
			}
		}

		if (enemy->GetHitProtect().IsAlreadyHit(&_player))
		{
			continue;
		}
		//UŒ‚”»’è
		for (auto& attackBox : enemy->GetHitBox()->GetAttackBoxes())
		{
			if (_col->IsHit(attackBox.rc, _player.GetRect()))
			{
				if (_player.IsAvoidance())
				{
					_player.SlowMotion(enemy);
					_player.SlowMotion();
				}
				else
				{
					_player.Damage(attackBox.power, attackBox);
					_player.HitStop(attackBox.hitstop);
					enemy->HitStop(attackBox.hitstop);
					enemy->GetHitProtect().Hit(&_player);
					if (attackBox.power > 50)
					{
						_camera.Quake(Vector2(10, 0));
					}
				}
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
		//if (bullet->GetObjType() == ObjectType::enemy)
		//{
		//	continue;
		//}
		for (auto& block : BlockManager::Instance().GetBlockList())
		{
			hitFlag = _col->IsHit(block->GetRect(), bullet->GetCircle());

			if (hitFlag)
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
				_player.GetCombo().Hit();
				bullet->Finalize();
				break;
			}
		}
	}
}

void 
GameScene::PlayerColFood()
{
	for (auto& food : _foodManager.GetFoodList())
	{
		if (!food->IsCollect())
		{
			continue;
		}

		if (_col->IsHit(_player.GetRect(), food->GetRect()))
		{
			food->Hit(&_player);
			_score.Add(food->GetScore());
		}
	}
}

void 
GameScene::FoodColBlock()
{
	bool hitFlag = false;
	for (auto& food : _foodManager.GetFoodList())
	{
		if (food->IsDelete())
		{
			continue;
		}
		if (food->IsCollect())
		{
			continue;
		}
		//if (bullet->GetObjType() == ObjectType::enemy)
		//{
		//	continue;
		//}
		for (auto& block : BlockManager::Instance().GetBlockList())
		{
			hitFlag = _col->IsHit(block->GetRect(), food->GetRect());

			if (hitFlag)
			{
				food->Hit(block);
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
	PlayerColFood();
	FoodColBlock();
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

	if (_sceneChangeFlag)
	{
		SceneManager::Instance().LogoState(_logoState);
		SceneManager::Instance().ChangeScene(SceneType::result);
	}
}