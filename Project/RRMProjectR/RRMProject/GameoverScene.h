#pragma once

#include "Scene.h"
#include "Rect.h"
#include "Arrow.h"
class Input;
class SceneManager;
enum class NEXT_SCENE
{
	game,
	menu
};

enum class UpdateState
{
	normal,
	end,
	max
};

enum class GameOverUI: unsigned int
{
	conti,
	yes,
	no,
	max
};

class GameoverScene : public Scene
{
private:
	int _bgHandle;
	int _logoHandle[(int)GameOverUI::max];
	Rect _logoRect[(int)GameOverUI::max];
	Input* _input;
	Arrow* _arrow;
	int _stageId;
	NEXT_SCENE _nextScene;
	UpdateState _state;
	int _totalScore;
	int _continueStock;

	int _gameoverLogo;
	Vector2 _gameoverPos;

	int _arrowState;
	
	void ImageLoad();

	void RightMove();
	void LeftMove();

	void NormalUpdate();
	void EndUpdate();

	using GameOverUpdate = void(GameoverScene::*)();

	GameOverUpdate _update[(int)UpdateState::max] =
	{
		&GameoverScene::NormalUpdate,
		&GameoverScene::EndUpdate
	};

	void ChangeScene();
public:
	GameoverScene();
	GameoverScene(int score);
	~GameoverScene();

	bool Update();
	void Draw();
};

