#include "TitleScene.h"
#include <DxLib.h>
#include "Fade.h"


TitleScene::TitleScene()
{
	Fade::Instance().FadeOut(3.0f);
	_timer.Start();
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
	return true;
}
