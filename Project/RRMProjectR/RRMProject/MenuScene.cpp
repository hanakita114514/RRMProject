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
	_titleHandle = RRMLib::LoadGraph("Resource/img//logo/gameStart.png");
	_update = &MenuScene::TitleUpdate;
	_input = InputFactory::Create(InputMode::pad, 0);

	for (int i = 0; i < (int)(LogoIdx::logoMax); i++)
	{
		_logo[i].image = RRMLib::LoadGraph("Resource/img/UI/Arrow_Smile.png");
		_logo[i].rc.pos = Vector2((float)(WINDOW_WIDTH / 3), (float)(WINDOW_HEIGHT / 3 * (i + 1)));
		_logo[i].rc.h = LogoHeight;
		_logo[i].rc.w = LogoWidth;

		_logoDefaultPos[i] = _logo[i].rc.pos;
		_logo[i].freamCnt = 0;
	}

	_arrow.SetPos(_logo[0].rc.pos);

	_menuInfo.Init();

	_bg = RRMLib::LoadGraph("Resource/img/BackGround/Bg_Grassland.jpg");

	right = false;
	left = false;
	up = false;;
	down = false;
	_logoIdx = 0;
	_stageId = 0;

	_toolIdx = 0;
	_weaponIdx = 0;

	_freamCnt = 0;
	_velocity = {};

	GameMain::Instance().EqiupDataCopy(_data);

}


MenuScene::~MenuScene()
{
	delete _input;
}

void 
MenuScene::TitleUpdate()
{
	RRMLib::DrawExtendGraph(340, 260, 940, 460, _titleHandle);
	if (_input->Start())
	{
		Fade::Instance().FadeIn(5.0f);
	}

	if (Fade::Instance().IsFadeInEnd())
	{
		_update = &MenuScene::MenuUpdate;
	}
}

void 
MenuScene::MenuUpdate()
{
	if (Fade::Instance().IsFadeOutEnd() || !Fade::Instance().IsPause())
	{
		UpMove();
		DownMove();

		//Bボタン（決定ボタン）がおされたのなら---------------------------------------
		if (_input->IsTriger(KeyType::keyB))
		{
			switch (_logoIdx)
			{
			case 0:
			{
				_stageId = 0;
				_update = &MenuScene::GameStart;
				_logoIdx = 0;
				_arrow.SetPos(_logoDefaultPos[_logoIdx]);
				_menuInfo.Enlargement(40,127);
			}
			break;
			case 1:
			{
				_update = &MenuScene::Configuration;
				_logoIdx = 0;
				_arrow.SetPos(_logoDefaultPos[_logoIdx]);
				_menuInfo.Enlargement(40,127);
			}
			break;
			default:
				break;
			}
		}
		//---------------------------------------------------------------------------------
		_arrow.Draw();
		for (int i = 0; i < (int)(LogoIdx::logoMax); i++)
		{
			RRMLib::DrawGraph(_logo[i].rc.pos.x, _logo[i].rc.pos.y, _logo[i].image);
		}
		LogoMove();
	}

	if (Fade::Instance().IsFadeInEnd())
	{
		Fade::Instance().FadeOut(10.0f);
	}

	
}

void 
MenuScene::GameStart()
{
	if (_menuInfo.IsWait())
	{
		UpMove();
		DownMove();

		if (Exit())
		{
			_update = &MenuScene::MenuUpdate;
			_logoIdx = 0;
			_arrow.SetPos(_logoDefaultPos[_logoIdx]);
			_menuInfo.Reduction(50);
		}
		else if (_input->IsTriger(KeyType::keyB))
		{
			switch (_logoIdx)
			{
			case 0:
			{
				_stageId = 0;
				Fade::Instance().FadeIn(10.0f);
			}
			break;
			case 1:
			{
				_stageId = 0;
				_update = &MenuScene::StageSelect;
			}
			break;
			default:
				break;
			}

			_logoState = static_cast<LogoIdx>(_logoIdx);
		}
		_arrow.Draw();
		LogoMove();

		for (int i = 0; i < (int)(LogoIdx::logoMax); i++)
		{
			RRMLib::DrawGraph(_logo[i].rc.pos.x, _logo[i].rc.pos.y, _logo[i].image);
		}
	}


	//ゲームシーンへの遷移
	if (Fade::Instance().IsFadeInEnd())
	{
		MapManager::Instance().StageSelect(_stageId);
		SceneManager::Instance().ChangeScene(SceneType::game);
		//GameMain::Instance().ChangeScene(new GameScene(_logoState));
	}

}

void
MenuScene::StageSelect()
{
	_stageId = RightMove(_stageId, (int)Stage::stageMax);
	_stageId = LeftMove(_stageId, (int)Stage::stageMax);

	if (_menuInfo.IsWait())
	{
		if (_input->IsTriger(KeyType::keyB))
		{
			Fade::Instance().FadeIn(10.0);
		}

		if (Exit())
		{
			_update = &MenuScene::GameStart;
		}
	}

	if (Fade::Instance().IsFadeInEnd())
	{
		MapManager::Instance().StageSelect(_stageId);
		SceneManager::Instance().ChangeScene(SceneType::game);
		//GameMain::Instance().ChangeScene(new GameScene(_logoState));
	}

}
void
MenuScene::Configuration()
{
	if (_menuInfo.IsWait())
	{
		UpMove();
		DownMove();

		if (Exit())
		{
			_update = &MenuScene::MenuUpdate;
			_logoIdx = 0;
			_arrow.SetPos(_logoDefaultPos[_logoIdx]);
			_menuInfo.Reduction(50);
		}

		_arrow.Draw();
		LogoMove();

		for (int i = 0; i < (int)(LogoIdx::logoMax); i++)
		{
			RRMLib::DrawGraph(_logo[i].rc.pos.x, _logo[i].rc.pos.y, _logo[i].image);
		}
	}
}

void MenuScene::Draw()
{
	RRMLib::DrawGraph(0, 0, _bg);
	_menuInfo.Draw();
}

void
MenuScene::LogoMove()
{
	switch (_logoIdx)
	{
	case static_cast<int>(LogoIdx::GameStart):
	{
		for (int i = 0; i < (int)(LogoIdx::logoMax); i++)
		{
			if (i == static_cast<int>(LogoIdx::GameStart))
			{
				_logo[i].rc.pos = ImageShaker(_logo[i].rc);
				continue;
			}

			_logo[i].rc.pos = _logoDefaultPos[i];
			_logo[i].freamCnt = 0;
		}
	}
	break;
	case static_cast<int>(LogoIdx::StageSelect) :
	{
		for (int i = 0; i < (int)(LogoIdx::logoMax); i++)
		{
			if (i == static_cast<int>(LogoIdx::StageSelect))
			{
				_logo[i].rc.pos = ImageShaker(_logo[i].rc);
				continue;
			}
			_logo[i].rc.pos = _logoDefaultPos[i];
			_logo[i].freamCnt = 0;
		}
	}
	break;
	default:
		break;
	}
}

Vector2
MenuScene::ImageShaker(Rect& rect)
{
	Vector2 pos = rect.pos;
	_logo[_logoIdx].freamCnt++;

	pos.x += sin(RAD * (_logo[_logoIdx].freamCnt * 2));
	pos.y -= cos(RAD * (_logo[_logoIdx].freamCnt * 2));

	return pos;
}

bool MenuScene::Update()
{
	_input->Update();

	Draw();
	_menuInfo.Update();
	(this->*_update)();
	return true;
}


bool
MenuScene::IsStickRight()
{
	prevRight = right;
	right = _input->Right();

	if (right & (right ^ prevRight))
	{
		return true;
	}

	return false;
}

bool
MenuScene::IsStickLeft()
{
	prevLeft = left;
	left = _input->Left();

	if (left & (left ^ prevLeft))
	{
		return true;
	}
	return false;
}

bool
MenuScene::IsStickUp()
{
	prevUp = up;
	up = _input->Up();

	if (up & (up ^ prevUp))
	{
		return true;
	}
	return false;
}

bool
MenuScene::IsStickDown()
{
	prevDown = down;
	down = _input->Down();

	if (down & (down ^ prevDown))
	{
		return true;
	}
	return false;
}

void
MenuScene::UpMove()
{
	if (IsStickUp())
	{
		_logoIdx = (_logoIdx + 1) % (int)LogoIdx::logoMax;
		_velocity = _logoDefaultPos[_logoIdx] - 
									_logoDefaultPos[((_logoIdx + ((int)LogoIdx::logoMax - 1)) % (int)LogoIdx::logoMax)];
	}
	_arrow.Move(_velocity);

	_velocity = { 0,0 };
}

void
MenuScene::DownMove()
{
	if (IsStickDown())
	{
		_logoIdx = (_logoIdx + 1) % (int)LogoIdx::logoMax;
		_velocity = _logoDefaultPos[_logoIdx] - _logoDefaultPos[((_logoIdx + 1) % (int)LogoIdx::logoMax)];
	}
	_arrow.Move(_velocity);

	_velocity = { 0,0 };
}

bool 
MenuScene::Exit()
{
	if (_input->IsTriger(KeyType::keyA))
	{
		_logoIdx = 0;
		return true;
	}

	return false;
}

int MenuScene::RightMove(int& idx, int idxMax)
{
	if (IsStickRight())
	{
		idx = (idx + idxMax) % idxMax;
	}

	return idx;
}

int MenuScene::LeftMove(int idx, int idxMax)
{
	if (IsStickLeft())
	{
			idx = ((idx + (idxMax - 1)) % idxMax);
	}

	return idx;
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