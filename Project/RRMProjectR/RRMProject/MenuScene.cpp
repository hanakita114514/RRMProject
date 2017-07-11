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
	_logo.image = RRMLib::LoadGraph("Resource/img/UI/startGame.png");
	_logo.rc.pos = Vector2(640, 360);

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
MenuScene::TitleUpdate()
{
}

void 
MenuScene::MenuUpdate()
{
	if (_input->Decision() && _isInput)
	{
		_menuInfo.ChangeState();
		_menuInfo.Enlargement(200);
		_isInput = false;
	}

	if (_menuInfo.IsState() == MenuState::none)
	{
		RRMLib::DrawGraph(_logo.rc.pos.x, _logo.rc.pos.y, _logo.image);
		_isInput = true;
	}
}

void 
MenuScene::GameStart()
{
	//if (_menuInfo.IsWait())
	//{
	//	UpMove();
	//	DownMove();

	//	if (Exit())
	//	{
	//		_update = &MenuScene::MenuUpdate;
	//		_logoIdx = 0;
	//		_arrow.SetPos(_logoDefaultPos[_logoIdx]);
	//		_menuInfo.Reduction(50);
	//	}
	//	else if (_input->IsTriger(KeyType::keyB))
	//	{
	//		switch (_logoIdx)
	//		{
	//		case 0:
	//		{
	//			_stageId = 0;
	//			Fade::Instance().FadeIn(10.0f);
	//		}
	//		break;
	//		case 1:
	//		{
	//			_stageId = 0;
	//			_update = &MenuScene::StageSelect;
	//		}
	//		break;
	//		default:
	//			break;
	//		}

	//		_logoState = static_cast<LogoIdx>(_logoIdx);
	//	}
	//	_arrow.Draw();
	//	LogoMove();

	//	for (int i = 0; i < (int)(LogoIdx::logoMax); i++)
	//	{
	//		RRMLib::DrawGraph(_logo[i].rc.pos.x, _logo[i].rc.pos.y, _logo[i].image);
	//	}
	//}


	////ƒQ[ƒ€ƒV[ƒ“‚Ö‚Ì‘JˆÚ
	//if (Fade::Instance().IsFadeInEnd())
	//{
	//	MapManager::Instance().StageSelect(_stageId);
	//	SceneManager::Instance().ChangeScene(SceneType::game);
	//	//GameMain::Instance().ChangeScene(new GameScene(_logoState));
	//}

}

void
MenuScene::StageSelect()
{
	//_stageId = RightMove(_stageId, (int)Stage::stageMax);
	//_stageId = LeftMove(_stageId, (int)Stage::stageMax);

	//if (_menuInfo.IsWait())
	//{
	//	if (_input->IsTriger(KeyType::keyB))
	//	{
	//		Fade::Instance().FadeIn(10.0);
	//	}

	//	if (Exit())
	//	{
	//		_update = &MenuScene::GameStart;
	//	}
	//}

	//if (Fade::Instance().IsFadeInEnd())
	//{
	//	MapManager::Instance().StageSelect(_stageId);
	//	SceneManager::Instance().ChangeScene(SceneType::game);
	//	//GameMain::Instance().ChangeScene(new GameScene(_logoState));
	//}

}
void
MenuScene::Configuration()
{
	//if (_menuInfo.IsWait())
	//{
	//	UpMove();
	//	DownMove();

	//	if (Exit())
	//	{
	//		_update = &MenuScene::MenuUpdate;
	//		_logoIdx = 0;
	//		_arrow.SetPos(_logoDefaultPos[_logoIdx]);
	//		_menuInfo.Reduction(50);
	//	}

	//	_arrow.Draw();
	//	LogoMove();

	//	for (int i = 0; i < (int)(LogoIdx::logoMax); i++)
	//	{
	//		RRMLib::DrawGraph(_logo[i].rc.pos.x, _logo[i].rc.pos.y, _logo[i].image);
	//	}
	//}
}

void MenuScene::Draw()
{
	RRMLib::DrawGraph(0, 0, _bg);
	_menuInfo.Draw();
}

void
MenuScene::LogoMove()
{
	//switch (_logoIdx)
	//{
	//case static_cast<int>(LogoIdx::GameStart):
	//{
	//	for (int i = 0; i < (int)(LogoIdx::logoMax); i++)
	//	{
	//		if (i == static_cast<int>(LogoIdx::GameStart))
	//		{
	//			_logo[i].rc.pos = ImageShaker(_logo[i].rc);
	//			continue;
	//		}

	//		_logo[i].rc.pos = _logoDefaultPos[i];
	//		_logo[i].freamCnt = 0;
	//	}
	//}
	//break;
	//case static_cast<int>(LogoIdx::StageSelect) :
	//{
	//	for (int i = 0; i < (int)(LogoIdx::logoMax); i++)
	//	{
	//		if (i == static_cast<int>(LogoIdx::StageSelect))
	//		{
	//			_logo[i].rc.pos = ImageShaker(_logo[i].rc);
	//			continue;
	//		}
	//		_logo[i].rc.pos = _logoDefaultPos[i];
	//		_logo[i].freamCnt = 0;
	//	}
	//}
	//break;
	//default:
	//	break;
	//}
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