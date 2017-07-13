#include "MenuScene.h"
#include "Fade.h"
#include "GameMain.h"
#include "GameScene.h"
#include "MapManager.h"
#include "common.h"
#include <math.h>
#include "Circle.h"
#include "Mathematics.h"
#include <RRMLib.h>
#include "SceneManager.h"
#include "InputFactory.h"
#include "Filter.h"

const char* Stage[(int)Stage::stageMax] = 
{
	{"Stage1"},
	{"Stage2"},
	{"Stage3"},
	{"Stage4"}
};

MenuScene::MenuScene()
{
	_update = &MenuScene::MenuUpdate;
	_input = InputFactory::Create(InputMode::pad, 0);

	_menuInfo.Init();
	_logo.image = RRMLib::LoadGraph("Resource/img/UI/Press_Start.png");
	_logo.rc.pos = Vector2(WINDOW_WIDTH / 2 - 197, WINDOW_HEIGHT / 2 - 37);

	_bg = RRMLib::LoadGraph("Resource/img/BackGround/Bg_Grassland.jpg");

	_toolIdx = 0;
	_weaponIdx = 0;

	GameMain::Instance().EqiupDataCopy(_data);

	Fade::Instance().FadeOut(10);
	_isInput = true;

}


MenuScene::~MenuScene()
{
	delete _input;
}

void 
MenuScene::MenuUpdate()
{
	if (_input->IsTriger(KeyType::keyStart) && _isInput)
	{
		_menuInfo.ChangeState();
		_isInput = false;
	}

	if (_menuInfo.IsState() == MenuState::none)
	{
		RRMLib::DrawGraph(_logo.rc.pos.x, _logo.rc.pos.y, _logo.image);
		_isInput = true;
	}
}


void MenuScene::Draw()
{
	//RRMLib::DrawGraph(0, 0, _bg);
	//_menuInfo.Draw();
}


Vector2
MenuScene::ImageShaker(Rect& rect)
{
	//Vector2 pos = rect.pos;
	//_logo[_logoIdx].freamCnt++;

	//pos.x += sin(RAD * (_logo[_logoIdx].freamCnt * 2));
	//pos.y -= cos(RAD * (_logo[_logoIdx].freamCnt * 2));

	//return pos;

	return Vector2(0, 0);
}

bool MenuScene::Update()
{
	Draw();

	if (Fade::Instance().IsFadeOutEnd())
	{
		_input->Update();
		_menuInfo.Update();
		(this->*_update)();
	}

	if (Fade::Instance().IsFadeInEnd())
	{
		_menuInfo.ChangeScene();
	}
	return true;
}


void
MenuScene::TypeOfWeapons()
{

}

void
MenuScene::WeaponSelect()
{

}

void
MenuScene::ToolSelect()
{

}