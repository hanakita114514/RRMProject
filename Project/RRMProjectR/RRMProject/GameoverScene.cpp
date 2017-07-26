#include "GameoverScene.h"
#include "Input.h"
#include "InputFactory.h"
#include "RRMLib.h"
#include "common.h"
#include "Fade.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "SceneManager.h"


#include <thread>

char* filePath[3] = 
{
	{"Resource/img/UI/Logo/Continue.png"},
	{"Resource/img/UI/Logo/Yes.png"},
	{"Resource/img/UI/Logo/No.png"}
};

const int Continue_Logo_X = 340;
const int Continue_Logo_Y = 104;
const int Yes_Logo_X = 152;
const int Yes_Logo_Y = 104;
const int No_Logo_X = 140;
const int No_Logo_Y = 101;
const int GameOver_Logo_X = 453;
const int GameOver_Logo_Y = 111;

GameoverScene::GameoverScene()
{
	_input = InputFactory::Create(InputMode::pad, 0);

	Rect r = {};
	r.pos = Vector2(WINDOW_WIDTH / 2 - Continue_Logo_X / 2, WINDOW_HEIGHT / 3 - Continue_Logo_Y / 2);
	r.h = Continue_Logo_Y;
	r.w = Continue_Logo_X;
	_logoRect[(int)GameOverUI::conti] = r;

	r.pos = Vector2(_logoRect[(int)GameOverUI::conti].Left() - Yes_Logo_X / 2, WINDOW_HEIGHT / 3 * 2 - Yes_Logo_Y / 2);
	r.h = Yes_Logo_Y;
	r.w = Yes_Logo_X;
	_logoRect[(int)GameOverUI::yes] = r;

	r.pos = Vector2(_logoRect[(int)GameOverUI::conti].Right() - No_Logo_X / 2, WINDOW_HEIGHT / 3 * 2 - No_Logo_Y / 2);
	r.h = Yes_Logo_Y;
	r.w = Yes_Logo_X;
	_logoRect[(int)GameOverUI::no] = r;

	_arrow = new Arrow(_logoRect[(int)GameOverUI::yes].pos);

	_gameoverLogo = RRMLib::LoadGraph("Resource/img/UI/Logo/GameOver.png");
	_gameoverPos = Vector2(WINDOW_WIDTH / 2 - GameOver_Logo_X / 2, WINDOW_HEIGHT / 2 - GameOver_Logo_Y / 2);

	ImageLoad();
	Fade::Instance().FadeOut(10.0f);
	_arrowState = 1;

	_state = UpdateState::normal;
}


GameoverScene::~GameoverScene()
{
	delete _arrow;
	delete _input;
}

bool GameoverScene::Update()
{
	_input->Update();

	(this->*_update[(int)_state])();
	return true;
}

void 
GameoverScene::NormalUpdate()
{
	RightMove();
	LeftMove();

	if (_input->Decision())
	{
		switch (_arrowState)
		{
		case (int)GameOverUI::yes:
		{
			_nextScene = NEXT_SCENE::game;
		}
		break;
		case (int)GameOverUI::no:
		{
			_nextScene = NEXT_SCENE::menu;
		}
		break;
		default:
			break;
		}
		_state = UpdateState::end;
	}

	_arrow->SetPos(_logoRect[_arrowState].pos);
	Draw();

}

void
GameoverScene::EndUpdate()
{
	if (_arrowState == (int)GameOverUI::no)
	{
		RRMLib::DrawGraph(_gameoverPos.x, _gameoverPos.y, _gameoverLogo, true);
	}
	ChangeScene();
}

void
GameoverScene::Draw()
{
	for (int i = 0; i < (int)GameOverUI::max; i++)
	{
		RRMLib::DrawGraph(_logoRect[i].pos.x, _logoRect[i].pos.y, _logoHandle[i], true);
	}

	_arrow->Draw();
}

void
GameoverScene::ImageLoad()
{
	for (int i = 0; i < (int)GameOverUI::max; i++)
	{
		_logoHandle[i] = RRMLib::LoadGraph(filePath[i]);
	}
}

void
GameoverScene::RightMove()
{
	if (_input->RightStickTriger())
	{
		_arrowState++;
		if (_arrowState > (int)GameOverUI::no)
		{
			_arrowState = (int)GameOverUI::yes;
		}
	}
}

void 
GameoverScene::LeftMove()
{
	if (_input->LeftStickTriger())
	{
		_arrowState--;
		if (_arrowState > (int)GameOverUI::yes)
		{
			_arrowState = (int)GameOverUI::no;
		}
	}
}

void
GameoverScene::ChangeScene()
{
	if (Fade::Instance().IsFadeOutEnd())
	{
		Fade::Instance().FadeIn(5.0f);
	}

	if (Fade::Instance().IsFadeInEnd())
	{
		if (_nextScene == NEXT_SCENE::game)
		{
			SceneManager::Instance().ChangeScene(SceneType::game);
			SceneManager::Instance().LogoState(_logoState);
		}
		else
		{
			SceneManager::Instance().ChangeScene(SceneType::menu);
		}
	}
}