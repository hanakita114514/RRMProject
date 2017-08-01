#pragma once

#include "Scene.h"
#include "Player.h"
#include "Camera.h"
#include "StatusUI.h"
#include "KeyConfig.h"
#include "Timer.h"
#include "InformationUI.h"
#include "Score.h"
#include "SoundManager.h"
#include <map>

#include "FoodManager.h"

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
		gameover,
	};

private:
	bool _sceneChangeFlag;

	Player _player;
	Collision* _col;
	StatusUI _statusUI;
	SoundType _soundType;

	FoodManager _foodManager;

	Input* _input;
	
	Camera _camera;

	typedef void(GameScene::*_func)();

	std::map<SceneState, _func> _update;
	void StartUpdate();
	void GameUpdate();
	void EndUpdate();
	void ResultUpdate();
	void GameOverUpdate();
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
	void PlayerColFood();
	void FoodColBlock();

	void ColProcess();

	void StageClear();

	void GameOver();

	void BGMSelect();

	void Initialize();

public:
	GameScene();
	GameScene(LogoIdx state, KeyData& keyData);
	~GameScene();

	bool Update();
};

