#pragma once

#include "Scene.h"
#include "Vector2.h"
#include "Arrow.h"

class DInput;

class MenuScene : public Scene
{
private:
	int _titleHandle;
	int _gameStartLogo;			//ロゴの画像ハンドル
	int _stageId;				//ステージID
	DInput* _dinput;

	Position _logoPosition;		//ロゴの位置
	Arrow _arrow;				//矢印

	bool prevRight, prevLeft;	//前フレームのスティック情報
	bool right, left;			//現フレームのスティック情報
	bool _fadeOutIn;			//フェードアウト検知用フラグ

	void (MenuScene::*_update)();

	void TitleUpdate();
	void MenuUpdate();

	void GameStart();
	void StageSelect();
public:
	MenuScene();
	~MenuScene();

	bool Update();

};

