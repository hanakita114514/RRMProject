#include "GameMain.h"
#include "common.h"
#include <DxLib.h>
#include "OfficialScene.h"
#include "Fade.h"
#include "DInput.h"
#include "Player.h"
#include "BulletManager.h"
#include "MapManager.h"
#include "EnemyManager.h"
#include "Collision.h"
#include "MapRendar.h"
#include "EnemyFactory.h"
#include "GameScene.h"
#include "MenuScene.h"
#include <RRMLib.h>
#include <string.h>
#include "SceneManager.h"

#include "FPS.h"
#include "Keyboard.h"

GameMain::GameMain()
{
}


GameMain::~GameMain()
{
}

bool GameMain::Init()
{
	//MessageBox(nullptr, "フルスクリーンで起動しますか？", "RRMProject", MB_YESNO);

	if(RRMLib::RRMLib_Init() == -1)
	{
		return false;
	}
	RRMLib::ChangeFullScreenMode(false);
	RRMLib::SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	//if (RRMLib::RRMLib_Init() == -1)  //DXライブラリ初期化
	//{
	//	return false;
	//}
	//RRMLib::ChangeWindowMode(true);
	//RRMLib::SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, COLOR_BIT);
	//RRMLib::SetDrawScreen(DX_SCREEN_BACK);

	_dataManager.Load(_data);

	Fade::Instance().Init();
	//_scene = new MenuScene();

	KeyData kd;
	_keyConfig.Load(kd);

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

	FPS fps;

	while (RRMLib::ProcessMessage() == 0 && loopOk)
	{
		RRMLib::ClearDrawScreen();

		fps.Update();

		//更新-----------------------
		Fade::Instance().Update();

		SceneManager::Instance().Update();

		//描画-----------------------
		Fade::Instance().Draw();

		fps.Draw();

		RRMLib::ScreenFlip();

	}
}

void GameMain::Terminate()
{
	RRMLib::RRMLib_End();
}

void
GameMain::DataUpdate(SaveData& data)
{
	_data = data;
}

void
GameMain::EqiupDataUpdata(const EquipmentInfometion& data)
{
	memcpy(_data.equipData.tool, data.tool, sizeof(data.tool));
	memcpy(_data.equipData.weapon, data.weapon, sizeof(data.weapon));
	_dataManager.Save(_data);
}

void
GameMain::EqiupDataCopy(EquipmentInfometion& data)
{
	memcpy(data.tool, _data.equipData.tool, sizeof(data.tool));
	memcpy(data.weapon, _data.equipData.weapon, sizeof(data.weapon));
}