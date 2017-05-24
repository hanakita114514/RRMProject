#include "GameMain.h"
#include "common.h"
#include <DxLib.h>
#include "OfficialScene.h"
#include "Fade.h"
#include "DInput.h"
#include "Player.h"
#include "BulletManeger.h"
#include "MapManeger.h"
#include "EnemyManeger.h"
#include "Collision.h"
#include "MapRendar.h"
#include "EnemyFactory.h"


GameMain::GameMain()
{
}


GameMain::~GameMain()
{
}

bool GameMain::Init()
{
	if (DxLib::DxLib_Init() == -1)  //DXライブラリ初期化
	{
		return false;
	}
	DxLib::ChangeWindowMode(true);
	DxLib::SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, COLOR_BIT);
	DxLib::SetDrawScreen(DX_SCREEN_BACK);

	Fade::Instance().Init();
	_scene = new OfficialScene();
	_enemy = new EnemyManeger();
	_map = new MapManeger();
	_map->Initialize();
	_bullet = new BulletManeger();
	_col = new Collision();
	CreateColBox();

	return true;
}

void
InputTest(DInput& input)
{

	if (input.Attack())
	{
		DxLib::DrawFormatString(0, 0, 0xffffffff, "攻撃");
	}
	if (input.Shoot())
	{
		DxLib::DrawFormatString(0, 15, 0xffffffff, "遠投");
	}
	if (input.Jump())
	{
		DxLib::DrawFormatString(0, 30, 0xffffffff, "ジャンプ");
	}
	if (input.Digestion())
	{
		DxLib::DrawFormatString(0, 45, 0xffffffff, "消化");
	}
	if (input.Left())
	{
		DxLib::DrawFormatString(0, 60, 0xffffffff, "左");
	}
	if (input.Right())
	{
		DxLib::DrawFormatString(0, 75, 0xffffffff, "右");
	}
	if (input.Up())
	{
		DxLib::DrawFormatString(0, 90, 0xffffffff, "上");
	}
	if (input.Down())
	{
		DxLib::DrawFormatString(0, 105, 0xffffffff, "下");
	}
	if (input.Avoidance())
	{
		DxLib::DrawFormatString(0, 120, 0xffffffff, "回避");
	}
	if (input.Parry())
	{
		DxLib::DrawFormatString(0, 135, 0xffffffff, "パリィ");
	}
	if (input.Select())
	{
		DxLib::DrawFormatString(0, 150, 0xffffffff, "セレクト");
	}
	if (input.Start())
	{
		DxLib::DrawFormatString(0, 165, 0xffffffff, "スタート");
	}
}

void GameMain::GameLoop()
{
	bool loopOk = true;

	DInput _dinput(DX_INPUT_PAD1);

	Player p(0);

	while (ProcessMessage() == 0 && loopOk)
	{
		DxLib::ClearDrawScreen();

		//Fade::Instance().Update();
		//loopOk = _scene->Update();
		//Fade::Instance().Draw();

		_dinput.Update();

		InputTest(_dinput);

		//更新-----------------------
		Fade::Instance().Update();

		p.Update();
		_map->Update();
		_enemy->Update();
		_bullet->Update();

		ColProcess(&p); //当たり判定

		//描画-----------------------
		Fade::Instance().Draw();
		_map->Draw();
		p.Draw();
		_enemy->Draw();
		_bullet->Draw();

		DxLib::ScreenFlip();

		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}
		for (auto a : _colBlock)
		{
			DxLib::DrawBox(a->GetRect().Left(), a->GetRect().Top(),
				a->GetRect().Right() + 1, a->GetRect().Bottom() + 1, 0xff0000, false);
		}

	}
}

void GameMain::Terminate()
{
	DxLib::DxLib_End();
}

void GameMain::ChangeScene(Scene* scene)
{
	delete _scene;
	_scene = scene;
}

void
GameMain::PlayerColBlock(Player *p)
{
	bool hitFlug = false;

	for (auto block : _colBlock)
	{
		Rect r = {};
		r = block->GetRect();
		hitFlug = _col->LineCross(p->GetRect(), p->GetVel(), r);
		if (hitFlug == true)
		{
			p->Hit(block);
			break;
		}
	
	}
}

void GameMain::EnemyColBlock()
{
	EnemyFactory* fac = _enemy->GetEnemyFac();
	fac->GetEnemyList();

	MapRendar* map = _map->GetMap();
	bool hitFlug;

	for (auto enemy : fac->GetEnemyList())
	{
		enemy->SetHitGround(false);
		for (auto block : _colBlock)
		{
			Rect r = {};
			r = block->GetRect();
			hitFlug = _col->LineCross(enemy->GetRect(), enemy->GetVel(), r);
			if (hitFlug == true)
			{
				enemy->Hit(block);
				break;
			}
		}
	}
}

void GameMain::PlayerColEnemy(Player* p)
{
	EnemyFactory* fac = _enemy->GetEnemyFac();
	fac->GetEnemyList();

	bool hitFlug;

	for (auto a : fac->GetEnemyList())
	{
			hitFlug = _col->IsHit(p->GetRect(), a->GetRect());
			if (hitFlug == true)
			{
				_col->PushBack(p->GetRect(), *a);
				break;
			}
	}
}

void
GameMain::BulletColPlayer(Player* p)
{
	bool hitFlug = false;

	BulletFactory* fac = _bullet->GetFactory();
	for (auto b : fac->Getlist())
	{
		hitFlug = _col->IsHit(p->GetGraze(), b->GetCircle());
		if (hitFlug == true && (p->GetObjType() != b->GetObjType()))
		{
			b->Hit(p);
			break;
		}

	}
}

void
GameMain::BulletColBlock()
{
	BulletFactory* fac = _bullet->GetFactory();
	bool hitFlug = false;

	for (auto bullet : fac->Getlist())
	{
		for (auto block : _colBlock)
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
GameMain::CreateColBox()
{
	Rect wr = {};

	MapRendar* map = _map->GetMap();
	std::vector<Block> b = map->GetBlockList();
	std::vector<Block>::iterator itr = b.begin();
	Rect r = {};
	r = itr->GetRect();

	for (itr; itr != b.end();)
	{
		if (itr == b.end() - 1)
		{
			Block* block = new Block();
			r.w += itr->GetRect().w;
			block->SetPos(r);
			_colBlock.push_back(block);
			break;
		}
		else if ((itr + 1)->GetRect().pos.x - itr->GetRect().pos.x == itr->GetRect().w)
		{
			r.w += itr->GetRect().w;
			++itr;
		}
		else
		{
			Block* block = new Block();
			block->SetPos(r);
			_colBlock.push_back(block);
			++itr;
			r = itr->GetRect();
		}
	}
	int i = 0;
}

void
GameMain::BulletColEnemy()
{
	BulletFactory* fac = _bullet->GetFactory();
	bool hitFlug = false;

	EnemyFactory* enemies = _enemy->GetEnemyFac();

	for (auto bullet : fac->Getlist())
	{
		for (auto enemy : enemies->GetEnemyList())
		{
			hitFlug = _col->IsHit(enemy->GetRect(), bullet->GetCircle());
			if (hitFlug == true && (enemy->GetObjType() != bullet->GetObjType()))
			{
				(bullet)->Hit(enemy);
				break;
			}
		}
	}

}

void 
GameMain::ColProcess(Player* p)
{
	PlayerColBlock(p);
	EnemyColBlock();
	BulletColBlock();
	BulletColPlayer(p);
	BulletColEnemy();
}