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
};

const int TITLE_IMAGE_WIDTH = 576;
const int TITLE_IMAGE_HEIGHT = 116;
const int LOGO_IMAGE_WIDTH = 394;
const int LOGO_IMAGE_HEIGHT = 74;

#define HALF(x)		(x / 2)
#define QUARTER(x)	(x / 4)

MenuScene::MenuScene()
{
	_update = &MenuScene::MenuUpdate;
	_input = InputFactory::Create(InputMode::pad, 0);

	_menuInfo.Init();
	_logo.image = RRMLib::LoadGraph("Resource/img/UI/Logo/Press_Start.png");
	_logo.rc.pos = Vector2(WINDOW_WIDTH / 2 - HALF(LOGO_IMAGE_WIDTH), WINDOW_HEIGHT / 3 * 2 - HALF(LOGO_IMAGE_HEIGHT));
	_logo.rc.w = LOGO_IMAGE_WIDTH;
	_logo.rc.h = LOGO_IMAGE_HEIGHT;
	_titleHandle = RRMLib::LoadGraph("Resource/img/UI/Logo/Title.png");

	_bg = RRMLib::LoadGraph("Resource/img/BackGround/StarDust.png");

	_toolIdx = 0;
	_weaponIdx = 0;

	GameMain::Instance().EqiupDataCopy(_data);

	Fade::Instance().FadeOut(10);
	_isInput = true;

	_animUV[0] = Vector2(0, 0);
	_animUV[1] = Vector2(1280, 0);
	_animUV[2] = Vector2(0, 960);
	_animUV[3] = Vector2(1280, 960);
	_animUV[4] = Vector2(0, 1920);
	_animUV[5] = Vector2(1280, 1920);
	_animUV[6] = Vector2(0, 2880);
	_animUV[7] = Vector2(1280, 2880);
	_animUV[8] = Vector2(0, 3840);
	_animUV[9] = Vector2(1280, 3840);

	_animCnt = 0;
	_frame = 0;
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
		SoundManager::Instance().PlayFromStart(SEType::decision);
		_menuInfo.ChangeState(MenuState::mainMenu);
		_isInput = false;
	}

	if (_menuInfo.IsState() == MenuState::none)
	{
		RRMLib::DrawGraph(_logo.rc.pos.x, _logo.rc.pos.y, _logo.image,true);
		RRMLib::DrawExtendGraph(_logo.rc.Left() - 200, _logo.rc.Top() - 340,
								_logo.rc.Right() + 200, _logo.rc.Top() - 140, _titleHandle, true, false);
		_isInput = true;
	}
}


void MenuScene::Draw()
{
	RRMLib::DrawRectGraph(0, 0, _animUV[(int)_animCnt].x, _animUV[(int)_animCnt].y,
							StarDust_Image_X, StarDust_Image_Y, _bg, true, true); ;
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
	_frame++;

	_animCnt = (int)(_frame * 0.5) % 10;

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