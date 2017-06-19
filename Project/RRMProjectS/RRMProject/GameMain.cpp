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


GameMain::GameMain()
{
}


GameMain::~GameMain()
{
}

bool GameMain::Init()
{

	if(RRMLib::RRMLib_Init() == -1)
	{
		return false;
	}
	RRMLib::ChangeFullScreenMode(false);
	RRMLib::SetWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);

	SaveData saveData;
	//if (RRMLib::RRMLib_Init() == -1)  //DX���C�u����������
	//{
	//	return false;
	//}
	//RRMLib::ChangeWindowMode(true);
	//RRMLib::SetGraphMode(WINDOW_WIDTH, WINDOW_HEIGHT, COLOR_BIT);
	//RRMLib::SetDrawScreen(DX_SCREEN_BACK);

	_dataManager.Load(_data);

	Fade::Instance().Init();
	_scene = new MenuScene();

	return true;
}

void
InputTest(DInput& input)
{

	if (input.Attack())
	{
		DxLib::DrawFormatString(0, 0, 0xffffffff, "�U��");
	}
	if (input.Shoot())
	{
		DxLib::DrawFormatString(0, 15, 0xffffffff, "����");
	}
	if (input.Jump())
	{
		DxLib::DrawFormatString(0, 30, 0xffffffff, "�W�����v");
	}
	if (input.Digestion())
	{
		DxLib::DrawFormatString(0, 45, 0xffffffff, "����");
	}
	if (input.Left())
	{
		DxLib::DrawFormatString(0, 60, 0xffffffff, "��");
	}
	if (input.Right())
	{
		DxLib::DrawFormatString(0, 75, 0xffffffff, "�E");
	}
	if (input.Up())
	{
		DxLib::DrawFormatString(0, 90, 0xffffffff, "��");
	}
	if (input.Down())
	{
		DxLib::DrawFormatString(0, 105, 0xffffffff, "��");
	}
	if (input.Avoidance())
	{
		DxLib::DrawFormatString(0, 120, 0xffffffff, "���");
	}
	if (input.Parry())
	{
		DxLib::DrawFormatString(0, 135, 0xffffffff, "�p���B");
	}
	if (input.Select())
	{
		DxLib::DrawFormatString(0, 150, 0xffffffff, "�Z���N�g");
	}
	if (input.Start())
	{
		DxLib::DrawFormatString(0, 165, 0xffffffff, "�X�^�[�g");
	}
}

void GameMain::GameLoop()
{
	bool loopOk = true;

	DInput _dinput(DX_INPUT_PAD1);

	while (RRMLib::ProcessMessage() == 0 && loopOk)
	{
		RRMLib::ClearDrawScreen();


		//�X�V-----------------------
		Fade::Instance().Update();

		loopOk = _scene->Update();

		//�`��-----------------------
		Fade::Instance().Draw();

		RRMLib::ScreenFlip();

		if (CheckHitKey(KEY_INPUT_ESCAPE))
		{
			break;
		}

	}
}

void GameMain::Terminate()
{
	RRMLib::RRMLib_End();
}

void GameMain::ChangeScene(Scene* scene)
{
	delete _scene;
	_scene = scene;
}

void
GameMain::DataUpdate(SaveData& data)
{
	_data = data;
}