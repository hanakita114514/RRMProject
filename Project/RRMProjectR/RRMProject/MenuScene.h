#pragma once

#include "Scene.h"
#include "Vector2.h"
#include "Arrow.h"
#include "Rect.h"
#include "DataManager.h"

#include "MenuInformation.h"
#include "Input.h"
#include <map>

class Input;

//ロゴ情報格納用構造体
class MenuScene : public Scene
{
	typedef struct LOGO
	{
		int image;
		Rect rc;
		float freamCnt;
	}Logo;

	enum class WeaponType
	{
		tool,
		closeCombat,
		max
	};

	const float LogoHeight = 64;
	const float LogoWidth = 52;

private:
	int _titleHandle;
	int _stageId;					//ステージID
	int _logoIdx;					//Logo構造体配列の添え字
	int _toolIdx;					//飛び道具配列の添え字
	int _weaponIdx;					//武器配列の添え字
	int _bg;						//背景の画像ハンドル
	float _freamCnt;

	MenuInformation _menuInfo;

	Arrow _arrow;				//矢印
	Logo _logo[(int)(LogoIdx::logoMax)];			//ロゴの画像ハンドル
	Input* _input;
	Vector2 _logoDefaultPos[(int)(LogoIdx::logoMax)];
	Vector2 _velocity;								//矢印の移動量
	EquipmentInfometion _data;

	bool prevRight, prevLeft,prevUp,prevDown;	//前フレームのスティック情報
	bool right, left,up,down;			//現フレームのスティック情報

	void (MenuScene::*_update)();
	void TitleUpdate();
	void MenuUpdate();
	void StageSelect();
	void GameStart();
	void Configuration();

	void Draw();

	void LogoMove();

	void UpMove();
	void DownMove();
	int RightMove(int& idx, int idxMax);
	int LeftMove(int idx, int idxMax);

	void TypeOfWeapons();

	void WeaponSelect();
	void ToolSelect();

	bool Exit();

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
