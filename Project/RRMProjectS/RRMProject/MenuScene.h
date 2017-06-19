#pragma once

#include "Scene.h"
#include "Vector2.h"
#include "Arrow.h"
#include "Rect.h"
class DInput;



//ロゴ情報格納用構造体
class MenuScene : public Scene
{
	typedef struct LOGO
	{
		int image;
		Rect rc;
		float freamCnt;
	}Logo;

	const float LogoHeight = 64;
	const float LogoWidth = 52;
private:
	int _titleHandle;
	int _stageId;					//ステージID
	int _logoIdx;					//Logo構造体配列の添え字
	int _bg;						//背景の画像ハンドル
	float _freamCnt;

	Arrow _arrow;				//矢印
	Logo _logo[(int)(LogoIdx::logoMax)];			//ロゴの画像ハンドル
	DInput* _dinput;
	Vector2 _logoDefaultPos[(int)(LogoIdx::logoMax)];

	bool prevRight, prevLeft,prevUp,prevDown;	//前フレームのスティック情報
	bool right, left,up,down;			//現フレームのスティック情報

	void (MenuScene::*_update)();

	void TitleUpdate();
	void MenuUpdate();
	void GameStart();
	void Configuration();

	void Draw();
	void LogoMove();

	Vector2 ImageShaker(Rect& rect);

public:
	MenuScene();
	~MenuScene();

	bool Update();

	bool IsStickRight();
	bool IsStickLeft();
	bool IsStickUp();
	bool IsStickDown();


};

