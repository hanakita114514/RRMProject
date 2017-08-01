#pragma once
#include "Rect.h"
#include "Arrow.h"
#include <map>
#include "DataManager.h"

enum class MenuState : unsigned int
{
	mainMenu,
	gameStart,
	stageSelect,
	configuration,
	volChange,

	none,
	max
};

struct LOGO
{
	int image;
	Rect rc;
};

enum class ArrowState
{
	up,
	down,
};

class Input;
class Number;
const int StageMax = 4;

class MenuInformation
{
private:
	int _handle;
	float _extendX;						//â°ïùÇÃägëÂíl
	float _extendY;						//ècïùÇÃägëÂíl
	int _ExRate;
	int _alpha;
	int _logoIdx;
	int _stageId;
	int _logoHandle[4][2];


	Vector2 _extendPos[2];
	Vector2 _numberUV[10];
	Vector2 drawPos[2];

	Input* _input;
	Arrow _arrow;
	LOGO _logo[2];
	Number* _bgmVolume;
	Number* _seVolume;
	SysData _configData;

	bool _isEnlargement;				//ägëÂíÜ
	bool _isReduction;					//èkè¨íÜ
	bool _isWait;						//ë“ã@íÜ
	MenuState _state;

	void (MenuInformation::*_update)();
	void Enlargement();
	void Reduction();
	void Wait();

	void MainMenu();
	void GameStart();
	void StageSelect();
	void Configuration();
	void VolChange();
	void None();


	using MenuInfo = void (MenuInformation::*)();

	MenuInfo _menuStatePtr[(int)MenuState::max] =
	{
		&MenuInformation::MainMenu,
		&MenuInformation::GameStart,
		&MenuInformation::StageSelect,
		&MenuInformation::Configuration,
		&MenuInformation::VolChange,
		&MenuInformation::None
	};

	void UpMove();
	void DownMove();
	void RightMove();
	void LeftMove();

	void VolumeChange(int& volume);

	void HandleSet(MenuState state);

public:
	MenuInformation();
	~MenuInformation();
	void Init();

	void Update();
	void Finalize();

	void Draw();

	void Enlargement(int extendRate, int alpha = 127);
	void Reduction(int extendRate);

	bool IsEnlargement() { return _isEnlargement; }
	bool IsReduction() { return _isReduction; }
	bool IsWait() { return _isWait; }
	MenuState IsState() { return _state; }

	void ChangeState(MenuState state = MenuState::mainMenu);
	void ChangeScene();
};

