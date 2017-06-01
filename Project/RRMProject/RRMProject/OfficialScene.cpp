#include "OfficialScene.h"
#include "GameMain.h"
#include "TitleScene.h"
#include <DxLib.h>
#include "common.h"
#include "Fade.h"



OfficialScene::OfficialScene() : _hp(100)
{
	_em.Create(EffectType::up, Position(400, 100));
	_em.Create(EffectType::down, Position(100, 200));
	_em.Create(EffectType::flash, Position(500, 300));
}


OfficialScene::~OfficialScene()
{
}

bool OfficialScene::Update()
{
	//----------çXêV----------------------------------------------------------------------------

	_hp.Damage(1);

	//----------ï`âÊ----------------------------------------------------------------------------
	DrawFormatString(100, 100, 0xffffffff, "Official Scene");

 	_em.Update();
	_em.Draw(Vector2(0, 0));


	_hpbar.Draw(Position(300,100), _hp);


	if (CheckHitKey(KEY_INPUT_RETURN) && Fade::Instance().IsWait())
	{
		Fade::Instance().FadeIn(5.0f);
	}
	if (Fade::Instance().IsFadeInEnd())
	{
		GameMain::Instance().ChangeScene(new TitleScene());
	}

	return true;
}

