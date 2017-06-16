#include "MenuScene.h"
#include <DxLib.h>
#include "DInput.h"
#include "Fade.h"
#include "GameMain.h"
#include "GameScene.h"
#include "MapManager.h"
#include "common.h"
#include <math.h>
#include "Circle.h"
#include "Mathematics.h"

const char* Stage[(int)Stage::stageMax] = 
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
	for (int i = 0; i < (int)(LogoIdx::logoMax); i++)
	{
		_logo[i].image = DxLib::LoadGraph("Resource/img/UI/Arrow_Smile.png");
		_logo[i].rc.pos = Vector2((float)(WINDOW_WIDTH / 3), (float)(WINDOW_HEIGHT / 3 * (i + 1)));
		_logo[i].rc.h = LogoHeight;
		_logo[i].rc.w = LogoWidth;

		_logoDefaultPos[i] = _logo[i].rc.pos;
		_logo[i].freamCnt = 0;
	}

	_arrow.SetPos(_logo[0].rc.pos);

	_bg = DxLib::LoadGraph("Resource/img/BackGround/mori.jpg");

	right = false;
	left = false;
	up = false;;
	down = false;
	_logoIdx = 0;
	_stageId = 0;

	_freamCnt = 0;
}


MenuScene::~MenuScene()
{
	delete _dinput;
}

void 
MenuScene::TitleUpdate()
{
	DxLib::DrawGraph(0, 0, _titleHandle, true);
	if (_dinput->Start())
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
		
		if (IsStickUp())
		{
			_logoIdx--;
			if (_logoIdx < 0)
			{
				_logoIdx = (int)(LogoIdx::logoMax) - 1;
			}
		}

		if (IsStickDown())
		{
			_logoIdx++;
			if (_logoIdx >= (int)(LogoIdx::logoMax))
			{
				_logoIdx = 0;
			}
		}


		//Bボタン（決定ボタン）がおされたのなら---------------------------------------
		if (_dinput->IsTriger(KeyType::keyB))
		{
			switch (_logoIdx)
			{
			case 0:
			{
				_stageId = 0;
				_update = &MenuScene::GameStart;
				_logoIdx = 0;
				Fade::Instance().PauseIn();
			}
			break;
			case 1:
			{
				//Fade::Instance().FadeIn(10.0);
			}
			break;
			default:
				break;
			}
		}
		//---------------------------------------------------------------------------------

	}

	if (Fade::Instance().IsFadeInEnd())
	{
		Fade::Instance().FadeOut(10.0f);
	}
	LogoMove();
	_arrow.SetPos(_logoDefaultPos[_logoIdx]);

	Draw();

	_arrow.Draw();
	for (int i = 0; i <(int)(LogoIdx::logoMax); i++)
	{
		DxLib::DrawGraph((int)_logo[i].rc.pos.x, (int)_logo[i].rc.pos.y, _logo[i].image, true);
	}
}

void 
MenuScene::GameStart()
{
	if (Fade::Instance().IsWait())
	{
		if (IsStickUp())
		{
			_logoIdx--;
			if (_logoIdx < 0)
			{
				_logoIdx = (int)(LogoIdx::logoMax) - 1;
			}
		}

		if (IsStickDown())
		{
			_logoIdx++;
			if (_logoIdx >= (int)(LogoIdx::logoMax))
			{
				_logoIdx = 0;
			}
		}

		if (_logoIdx == 1)
		{
			if (IsStickRight())	//右にスティックが倒されたか？
			{
				_stageId++;
				if (_stageId >= (int)Stage::stageMax)
				{
					_stageId = 0;
				}
			}

			if (IsStickLeft())		//左にスティックが倒されたか？
			{
				_stageId--;
				if (_stageId < 0)
				{
					_stageId = (int)Stage::stageMax - 1;
				}
			}
		}

		if (_dinput->IsTriger(KeyType::keyA))
		{
			_update = &MenuScene::MenuUpdate;
			_logoIdx = 0;
			Fade::Instance().PauseEnd();
		}
		else if (_dinput->IsTriger(KeyType::keyB))
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
				Fade::Instance().FadeIn(10.0);
			}
			break;
			default:
				break;
			}

			_logoState = static_cast<LogoIdx>(_logoIdx);

		}
		_arrow.SetPos(_logoDefaultPos[_logoIdx]);

		for (int i = 0; i < (int)(LogoIdx::logoMax); i++)
		{
			DxLib::DrawGraph((int)_logo[i].rc.pos.x, (int)_logo[i].rc.pos.y, _logo[i].image, true);
		}
		DrawString(0, 0, Stage[_stageId], 0xffffff);
	}

	LogoMove();
	_arrow.SetPos(_logoDefaultPos[_logoIdx]);

	_arrow.Draw();
	//ゲームシーンへの遷移
	if (Fade::Instance().IsFadeInEnd())
	{
		MapManager::Instance().StageSelect(_stageId);
		GameMain::Instance().ChangeScene(new GameScene(_logoState));
	}

}

void MenuScene::Draw()
{
	DxLib::DrawGraph(0, 0, _bg, true);
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
	_dinput->Update();
	(this->*_update)();

	return true;
}


bool
MenuScene::IsStickRight()
{
	prevRight = right;
	right = _dinput->Right();

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
	left = _dinput->Left();

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
	up = _dinput->Up();

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
	down = _dinput->Down();

	if (down & (down ^ prevDown))
	{
		return true;
	}
	return false;
}

