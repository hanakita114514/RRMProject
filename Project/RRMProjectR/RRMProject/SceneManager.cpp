#include "SceneManager.h"
#include "OfficialScene.h"
#include "TitleScene.h"
#include "MenuScene.h"
#include "GameScene.h"
#include "ResultScene.h"


SceneManager::SceneManager()
{
	_scene = new MenuScene();
}


SceneManager::~SceneManager()
{
	delete _scene;
}

void 
SceneManager::Update()
{
	_scene->Update();
}

void 
SceneManager::ChangeScene(SceneType type)
{
	switch (type)
	{
	case SceneType::official:
		delete _scene;
		_scene = new OfficialScene();
		break;
	case SceneType::title:
		delete _scene;
		_scene = new TitleScene();
		break;
	case SceneType::menu:
		delete _scene;
		_scene = new MenuScene();
		break;
	case SceneType::game:
		delete _scene;
		_scene = new GameScene(_logoState, _keyData);
		break;
	case SceneType::result:
		delete _scene;
		_scene = new ResultScene(_logoState);
		break;
	default:
		break;
	}
}

void 
SceneManager::ChangeScene(Scene* scene)
{
	delete _scene;
	_scene = scene;
}

void 
SceneManager::KeyConfig(KeyData& keyData)
{
	_keyData = keyData;
}

void 
SceneManager::LogoState(LogoIdx logoState)
{
	_logoState = logoState;
}