#include "OfficialScene.h"
#include "GameMain.h"
#include "TitleScene.h"
#include <RRMLib.h>
#include "common.h"
#include "Fade.h"
#include <math.h>
#include "EffectManager.h"
#include "SceneManager.h"

OfficialScene::OfficialScene() : _hp(100)
{
	EffectManager& em = EffectManager::Instance();
	em.Create(EffectType::up, Position(400, 100),Vector2(1.0f,1.0f));
	em.Create(EffectType::down, Position(100, 200), Vector2(3.0f, 1.0f));
	//em.Create(EffectType::flash, Position(500, 300),Vector2(1.0f,1.0f));
	em.Create(EffectType::explosion, Position(500, 300), Vector2(1.0f, 1.0f));
	em.Create(EffectType::erasure, Position(1000, 100), Vector2(0.1f, 0.1f));
	em.Create(EffectType::enemy_summons, Position(100, 300), Vector2(0.5f, 0.5f));
	em.Create(EffectType::bullet_summons, Position(300, 500), Vector2(1.0f, 1.0f));
	em.Create(EffectType::hit1, Position(700, 50), Vector2(1.0f, 1.0f));

	srand(time(NULL));
}


OfficialScene::~OfficialScene()
{
}

bool OfficialScene::Update()
{
	//----------çXêV----------------------------------------------------------------------------
	EffectManager& em = EffectManager::Instance();

	EffectType et = (EffectType)((rand() % ((unsigned int)EffectType::num - 1)) + 1);
	Vector2 pos;
	pos.x = rand() % WINDOW_WIDTH;
	pos.y = rand() % WINDOW_HEIGHT;
	int speed = rand() % 5 + 1;
	em.Create(et, pos, Vector2(1.0f, 1.0f), speed);

	_hp.Damage(1);

	//----------ï`âÊ----------------------------------------------------------------------------
	//DrawFormatString(100, 100, 0xffffffff, "Official Scene");

 	em.Update();
	em.Draw(Vector2(0, 0));



	if (Fade::Instance().IsFadeInEnd())
	{
		SceneManager::Instance().ChangeScene(SceneType::title);
	}
	if (Fade::Instance().IsWait())
	{
		Fade::Instance().FadeIn(5.0f);
	}
	return true;
}

