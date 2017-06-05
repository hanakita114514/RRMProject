#include "TitleScene.h"
#include <DxLib.h>
#include "Fade.h"
#include "DInput.h"
#include "GameMain.h"
#include "GameScene.h"

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
	DxLib::DrawFormatString(100, 100, 0xffffffff, "Title Scene");
	//DxLib::DrawFormatString(100, 200, 0xffffffff, "%d •ª %d •b", _timer.GetTime().mimutes, _timer.GetTime().seconds);
	DxLib::DrawFormatString(100, 200, 0xffffffff, "%d •ª", _timer.GetTime().mimutes);
	DxLib::DrawFormatString(100, 215, 0xffffffff, "%d •b", _timer.GetTime().seconds);
	DxLib::DrawFormatString(100, 230, 0xffffffff, "%d ƒ~ƒŠ•b", _timer.GetTime().millisec);

	_dinput->Update();

	if (_dinput->Start() && Fade::Instance().IsWait())
	{
		Fade::Instance().FadeIn(5.0f);
	}
	if (Fade::Instance().IsFadeInEnd())
	{
		GameMain::Instance().ChangeScene(new GameScene());
	}

	return true;
}
