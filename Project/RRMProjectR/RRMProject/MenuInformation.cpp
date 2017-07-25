#include "MenuInformation.h"
#include <RRMLib.h>
#include "common.h"
#include "Input.h"
#include "InputFactory.h"
#include "common.h"
#include "Fade.h"
#include "SceneManager.h"
#include "MapManager.h"
#include "Logo.h"
#include "Filter.h"

const float Y_ExtendLimit = 350;
const float X_ExtendLimit = 300;
const float Y_Draw_Offset = 50;
const int Number_Size = 64;

const char* filePath[] =
{
	"Resource/img/UI/Logo/startGame.png",
	"Resource/img/UI/Logo/setting.png",
	"Resource/img/UI/Logo/Start3.png",
	"Resource/img/UI/Logo/StageSelect.png",
	"Resource/img/UI/Logo/stage.png",
	"Resource/img/UI/Logo/Number/stageNumber.png",
	"Resource/img/UI/Logo/A.png",
	"Resource/img/UI/Logo/B.png",
};

MenuInformation::MenuInformation()
{
}


MenuInformation::~MenuInformation()
{
	RRMLib::DeleteGraph(_handle);
}

void 
MenuInformation::Init()
{
	_handle = RRMLib::LoadGraph("Resource/img/BackGround/whiteFilter.png");
	Rect r = {};
	_alpha = 0;

	_isReduction = false;
	_isEnlargement = false;
	_isWait = true;
	_extendX = _extendY = 0;
	_update = &MenuInformation::Wait;

	_extendPos[0] = Vector2(640, 350);
	_extendPos[1] = Vector2(640, 370);
	_state = MenuState::none;
	_input = InputFactory::Create(InputMode::keyboard, 0);
	
	int idx = 0;

	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 2; idx++)
		{
			_logoHandle[i][j] = RRMLib::LoadGraph(filePath[idx]);
			j++;
		}
	}

	_logo[0].rc.pos = Vector2(420, WINDOW_HEIGHT / 3);
	_logo[1].rc.pos = Vector2(420, WINDOW_HEIGHT / 3 * 2);
	HandleSet(MenuState::mainMenu);

	_arrow.SetPos(_logo[0].rc.pos);
	_logoIdx = 0;
	_stageId = 0;

	for (int i = 0; i < 10; i++)
	{
		_numberUV[i] = Vector2(64 * i, 0);
	}
}

void
MenuInformation::Update()
{
	_input->Update();
	(this->*_update)();
	(this->*_menuStatePtr[(int)_state])();
}

void
MenuInformation::Enlargement()
{
	_extendX += 40;

	if (_extendX > X_ExtendLimit)
	{
		_extendX = X_ExtendLimit;
		_extendY += 40;
	}
	if (_extendY > Y_ExtendLimit)
	{
		_extendY = Y_ExtendLimit;
		_update = &MenuInformation::Wait;
	}
}

void
MenuInformation::Reduction()
{
	_extendY -= 50;
	if (_extendY <= 0)
	{
		_extendY = 0;
		_extendX -= 50;
	}

	if (_extendX <= 0)
	{
		_extendX = 0;
		_alpha = 0;
		_update = &MenuInformation::Wait;
		_state = MenuState::none;
	}
}

void
MenuInformation::Wait()
{
	_isEnlargement = false;
	_isReduction = false;
	_isWait = true;
}

void
MenuInformation::None()
{

}

void
MenuInformation::MainMenu()
{
	UpMove();
	DownMove();

	int i = 0;
	if (_input->Decision())
	{
		switch (_logoIdx)
		{
		case 0:
		{
			_state = MenuState::gameStart;
			_logoIdx = 0;
			_arrow.SetPos(_logo[_logoIdx].rc.pos);
			HandleSet(_state);
		}
		break;
		case 1:
		{
			_state = MenuState::configuration;
			_logoIdx = 0;
			_arrow.SetPos(_logo[_logoIdx].rc.pos);
			HandleSet(_state);
		}
		break;
		default:
			break;
		}
	}

	if (_input->Exit())
	{
		_state = MenuState::none;
	}

	if (IsWait())
	{
		for (int i = 0; i < 2; i++)
		{
			RRMLib::DrawGraph(_logo[i].rc.pos.x, _logo[i].rc.pos.y - Y_Draw_Offset, _logo[i].image, true);
		}
		_arrow.Draw();
	}
}

void 
MenuInformation::GameStart()
{
	if (IsWait())
	{
		UpMove();
		DownMove();

		for (int i = 0; i < 2; i++)
		{
			RRMLib::DrawGraph(_logo[i].rc.pos.x, _logo[i].rc.pos.y - Y_Draw_Offset , _logo[i].image, true);
		}
		_arrow.Draw();

		if (_input->Decision())
		{
			switch (_logoIdx)
			{
			case 0:
			{
				Fade::Instance().FadeIn(10.0);
				SceneManager::Instance().LogoState(LogoIdx::GameStart);
			}
			break;
			case 1:
			{
				_state = MenuState::stageSelect;
				_arrow.SetPos(_logo[_logoIdx].rc.pos);
				HandleSet(_state);
			}
			break;
			default:
				break;
			}
		}
		if (_input->Exit())
		{
			_state = MenuState::mainMenu;
			HandleSet(_state);
			_logoIdx = 0;
			_arrow.SetPos(_logo[_logoIdx].rc.pos);
		}

	}
}

void
MenuInformation::StageSelect()
{
	if (_input->Decision())
	{
		Fade::Instance().FadeIn(10.0);
		SceneManager::Instance().LogoState(LogoIdx::StageSelect);
	}

	if (_input->Exit())
	{
		_state = MenuState::gameStart;
		_logoIdx = 0;
		_stageId = 0;
		_arrow.SetPos(_logo[_logoIdx].rc.pos);
		HandleSet(_state);
	}


	RRMLib::DrawGraph(_logo[0].rc.pos.x, _logo[0].rc.pos.y - Y_Draw_Offset, _logo[0].image, true);
	RRMLib::DrawRectGraph(_logo[0].rc.pos.x + 300, _logo[0].rc.pos.y, _numberUV[_stageId].x, _numberUV[_stageId].y,
		Number_Size, Number_Size, _logo[1].image, true, false);

	RightMove();
	LeftMove();
}

void 
MenuInformation::Configuration()
{
	UpMove();
	DownMove();

	if (_input->Exit())
	{
		_state = MenuState::mainMenu;
		HandleSet(_state);
		_logoIdx = 0;
		_arrow.SetPos(_logo[_logoIdx].rc.pos);
	}
	if (_input->Decision())
	{
	}

	for (int i = 0; i < 2; i++)
	{
		RRMLib::DrawGraph(_logo[i].rc.pos.x, _logo[i].rc.pos.y - Y_Draw_Offset, _logo[i].image, true);
	}
	_arrow.Draw();

	RRMLib::DrawGraph(400, 100, _logoHandle[(int)MenuState::mainMenu][1],true);

}

void
MenuInformation::Enlargement(int extendRate, int alpha)
{
}

void 
MenuInformation::Reduction(int extendRate)
{
}

void
MenuInformation::Draw()
{
}

void
MenuInformation::RightMove()
{
	if (_input->RightStickTriger())
	{
		_stageId = (_stageId + 1) % 4;
	}
}

void
MenuInformation::LeftMove()
{
	if (_input->LeftStickTriger())
	{
		_stageId = (_stageId + 4 - 1) % 4;
	}
}

void
MenuInformation::UpMove()
{
	Vector2 prevPos = _logo[_logoIdx].rc.pos;

	if (_input->UpStickTriger())
	{
		_logoIdx = (_logoIdx + 1) % 2;
	}

	Vector2 vel = _logo[_logoIdx].rc.pos - prevPos;

	_arrow.Move(vel);
}

void
MenuInformation::DownMove()
{
	Vector2 prevPos = _logo[_logoIdx].rc.pos;

	if (_input->DownStickTriger())
	{
		_logoIdx = (_logoIdx + 2 - 1) % 2;
	}

	Vector2 vel = _logo[_logoIdx].rc.pos - prevPos;

	_arrow.Move(vel);
}

void
MenuInformation::ChangeScene()
{
	MapManager::Instance().StageSelect(_stageId);
	SceneManager::Instance().ChangeScene(SceneType::game);
}

void
MenuInformation::ChangeState(MenuState state)
{
	_state = state;
}

void
MenuInformation::HandleSet(MenuState state)
{
	for (int i = 0; i < 2; i++)
	{
		_logo[i].image = _logoHandle[(int)state][i];
	}
}