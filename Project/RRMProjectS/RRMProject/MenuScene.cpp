#include "MenuScene.h"
#include <DxLib.h>
#include "DInput.h"
#include "Fade.h"
#include "GameMain.h"
#include "GameScene.h"
#include "MapManager.h"
#include "common.h"

const char* Stage[STAGE_ID_MAX] = 
{
	{"Stage1"},
	{"Stage2"},
	{"Stage3"},
	{"Stage4"}
};

MenuScene::MenuScene()
{
	_titleHandle = DxLib::LoadGraph("Resource/img/title.png");
	_update = &MenuScene::TitleUpdate;
	_dinput = new DInput(0);
	_stageId = 0;
	_gameStartLogo = DxLib::LoadGraph("Resource/img/1PLAYER_MODE.png");

	_logoPosition = Vector2(WINDOW_WIDTH / 3, WINDOW_HEIGHT / 3);
	_arrow.SetPos(_logoPosition);

	right = false;
	left = false;
	_fadeOutIn = false;
}


MenuScene::~MenuScene()
{

}

void 
MenuScene::TitleUpdate()
{
	DxLib::DrawGraph(0, 0, _titleHandle, true);
	if (_dinput->Start())
	{
		_update = &MenuScene::MenuUpdate;
	}
}

void 
MenuScene::MenuUpdate()
{
	_arrow.Draw();

	DxLib::DrawGraph(_logoPosition.x, _logoPosition.y, _gameStartLogo, true);
}

void 
MenuScene::GameStart()
{
	if (_dinput->IsPress(KeyType::keyA))
	{
		_update = &MenuScene::MenuUpdate;
	}

	Fade::Instance().FadeOut(10.0);

	if (Fade::Instance().IsFadeOutEnd())
	{
		GameMain::Instance().ChangeScene(new GameScene());
	}
}

void
MenuScene::StageSelect()
{
	prevRight = right;
	prevLeft = left;

	right = _dinput->Right();
	left = _dinput->Left();

	if (!_fadeOutIn)		//フェードアウト状態でないのなら
	{
		if (right & (right ^ prevRight))	//右にスティックが倒されたか？
		{
			_stageId++;
			if (_stageId > STAGE_ID_MAX)
			{
				_stageId = 0;
			}
		}

		if (left & (left ^ prevLeft))		//左にスティックが倒されたか？
		{
			_stageId--;
			if (_stageId < 0)
			{
				_stageId = STAGE_ID_MAX;
			}
		}

		if (_dinput->IsPress(KeyType::keyA))	//パッドのAボタンが押されたら
		{
			_update = &MenuScene::MenuUpdate;
		}
		else if (_dinput->IsPress(KeyType::keyB))
		{
			Fade::Instance().FadeOut(10.0);
			_fadeOutIn = true;
		}
	}

	if (Fade::Instance().IsFadeOutEnd())
	{
		GameMain::Instance().ChangeScene(new GameScene());
		MapManager::Instance().StageSelect(_stageId);
	}
}

bool MenuScene::Update()
{
	_dinput->Update();
	(this->*_update)();

	return true;
}
