#include "OfficialScene.h"
#include "GameMain.h"
#include "TitleScene.h"
#include <DxLib.h>
#include "common.h"
#include "Fade.h"

OfficialScene::OfficialScene()
{
	_testHandle = LoadGraph("Resource/img/mori.jpg");

}


OfficialScene::~OfficialScene()
{
}

bool OfficialScene::Update()
{
	//----------çXêV----------------------------------------------------------------------------

	//----------ï`âÊ----------------------------------------------------------------------------
	DrawFormatString(100, 100, 0xffffffff, "Official Scene");

	DxLib::DrawExtendGraph(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT, _testHandle, false);


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