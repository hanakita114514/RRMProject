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

const float Y_ExtendLimit = 350;
const float X_ExtendLimit = 300;

const char* filePath[] =
{
	"Resource/img/UI/GAME_START.png",
	"Resource/img/UI/setting.png",
	"Resource/img/UI/Start3.png",
	"Resource/img/UI/StageSelect.png",
	"Resource/img/UI/stage.png"
	"Resource/img/UI/stageNumber.png",
	"Resource/img/UI/A.png",
	"Resource/img/UI/B.png",
	"Resource/img/UI/C.png"
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
	_input = InputFactory::Create(InputMode::pad, 0);
	
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

	if (_state != MenuState::none)
	{
	}
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
		Reduction(0);
	}

	if (IsWait())
	{
		for (int i = 0; i < 2; i++)
		{
			RRMLib::DrawGraph(_logo[i].rc.pos.x, _logo[i].rc.pos.y, _logo[i].image);
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
			RRMLib::DrawGraph(_logo[i].rc.pos.x, _logo[i].rc.pos.y, _logo[i].image);
		}
		_arrow.Draw();

		if (_input->Decision())
		{
			switch (_logoIdx)
			{
			case 0:
			{
				Fade::Instance().FadeIn(10.0);
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

	}

	if (_input->Exit())
	{
		_state = MenuState::gameStart;
		_logoIdx = 0;
		_arrow.SetPos(_logo[_logoIdx].rc.pos);
		HandleSet(_state);
	}

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

	for (int i = 0; i < 2; i++)
	{
		RRMLib::DrawGraph(_logo[i].rc.pos.x, _logo[i].rc.pos.y, _logo[i].image);
	}
	_arrow.Draw();

	RRMLib::DrawGraph(400, 100, _logoHandle[(int)MenuState::mainMenu][1]);

}

void
MenuInformation::Enlargement(int extendRate, int alpha)
{
	_ExRate = extendRate;
	_isEnlargement = true;
	_isReduction = false;
	_isWait = false;
	_alpha = alpha;
	_extendX = 0;
	_extendY = 0;

	_update = &MenuInformation::Enlargement;
}

void 
MenuInformation::Reduction(int extendRate)
{
	_ExRate = extendRate;
	_isEnlargement = false;
	_isReduction = true;
	_isWait = false;

	_update = &MenuInformation::Reduction;
}

void
MenuInformation::Draw()
{
	RRMLib::SetBlendMode(RRM_BLENDMODE_ALPHA, (int)_alpha);
	RRMLib::DrawExtendGraph(_extendPos[0].x - _extendX, _extendPos[0].y - _extendY,
							_extendPos[1].x + _extendX, _extendPos[1].y + _extendY,_handle);
	RRMLib::SetBlendMode(RRM_BLENDMODE_NONE,0);
}

void
MenuInformation::RightMove()
{
	_stageId = (_stageId + 1 )% 4;
}

void
MenuInformation::LeftMove()
{
	_stageId = (_stageId + 4 - 1) % 4;
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