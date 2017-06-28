#include "ResultScene.h"
#include "DInput.h"
#include "Fade.h"
#include "GameMain.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "MapManager.h"
#include "SceneManager.h"

ResultScene::ResultScene()
{
	_dinput = new DInput(0);
	Fade::Instance().FadeOut(5.0f);
}

ResultScene::ResultScene(LogoIdx state)
{
	_dinput = new DInput(0);
	Fade::Instance().FadeOut(5.0f);
	_logoState = state;
	
}

ResultScene::~ResultScene()
{
	delete _dinput;
}

bool ResultScene::Update()
{
	_dinput->Update();

	switch (_logoState)
	{
	case LogoIdx::GameStart:
	{
		int i = 0;
		if (_dinput->IsTriger(KeyType::keyB))
		{
			Fade::Instance().FadeIn(10.0);
		}

		if (Fade::Instance().IsFadeInEnd())
		{
			if (!MapManager::Instance().NextStage())
			{
				SceneManager::Instance().ChangeScene(SceneType::menu);
			}
			else
			{
				SceneManager::Instance().ChangeScene(SceneType::game);
			}
		}
	}
		break;
	case LogoIdx::StageSelect:
	{
		if (_dinput->IsTriger(KeyType::keyStart))
		{
			Fade::Instance().FadeIn(10.0);
		}

		if (Fade::Instance().IsFadeInEnd())
		{
			SceneManager::Instance().ChangeScene(SceneType::menu);
		}

	}
		break;
	default:
		break;
	}
	return true;
}