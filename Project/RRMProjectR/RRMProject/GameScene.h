#pragma once

#include "Scene.h"
#include "Player.h"
#include "Camera.h"
#include "StatusUI.h"
#include "KeyConfig.h"
#include "Timer.h"
#include "InformationUI.h"
#include "Score.h"

#include <map>

class Collision;
class Input;
class Result;

class GameScene : public Scene
{
private:
	enum SceneState
	{
		start,
		game,
		end,
		result,
	};

private:
	bool _sceneChangeFlag;

	Player _player;
	Collision* _col;
	StatusUI _statusUI;

	Input* _input;
	
	Camera _camera;

	typedef void(GameScene::*_func)();

	std::map<SceneState, _func> _update;
	void StartUpdate();
	void GameUpdate();
	void EndUpdate();
	void ResultUpdate();
	SceneState _state;

	Result* _result;

	int _endFrame;

	Timer _time;

	Score _score;

	InformationUI _infoUI;

	void EnemyColBlock();
	void PlayerColBlock();
	void PlayerColEnemy();
	void BulletColPlayer();
	void BulletColBlock();
	void BulletColEnemy();

	void ColProcess();

	void StageClear();

public:
	GameScene();
	GameScene(LogoIdx state, KeyData& keyData);
	~GameScene();

	bool Update();
};

