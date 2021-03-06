#include "TitleScene.h"
#include <RRMLib.h>
#include "Fade.h"
#include "DInput.h"
#include "GameMain.h"
#include "GameScene.h"
#include "SceneManager.h"

TitleScene::TitleScene()
{
	Fade::Instance().FadeOut(3.0f);
	_timer.Start();

	_dinput = new DInput(0);
}


TitleScene::~TitleScene()
{
}

bool TitleScene::Update()
{
//	RRMLib::DrawFormatString(100, 100, 0xffffffff, "Title Scene");
	//RRMLib::DrawFormatString(100, 200, 0xffffffff, "%d �� %d �b", _timer.GetTime().mimutes, _timer.GetTime().seconds);
//	RRMLib::DrawFormatString(100, 200, 0xffffffff, "%d ��", _timer.GetTime().mimutes);
//	RRMLib::DrawFormatString(100, 215, 0xffffffff, "%d �b", _timer.GetTime().seconds);
//	RRMLib::DrawFormatString(100, 230, 0xffffffff, "%d �~���b", _timer.GetTime().millisec);

	_dinput->Update();

	if (_dinput->Start() && Fade::Instance().IsWait())
	{
		Fade::Instance().FadeIn(5.0f);
	}
	if (Fade::Instance().IsFadeInEnd())
	{
		SceneManager::Instance().ChangeScene(SceneType::menu);
		//GameMain::Instance().ChangeScene(new GameScene());
	}

	return true;
}
