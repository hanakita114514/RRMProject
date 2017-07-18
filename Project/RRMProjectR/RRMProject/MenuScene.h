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
const int StarDust_Anim_Max = 10;
const int StarDust_Image_X = 1280;
const int StarDust_Image_Y = 960;

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
	bool _isInput;
	float _animCnt;
	int _frame;


	Vector2 _animUV[StarDust_Anim_Max];
	MenuInformation _menuInfo;
	LOGO _logo;

	Arrow _arrow;				//矢印
	Input* _input;
	Vector2 _logoDefaultPos[(int)(LogoIdx::logoMax)];
	Vector2 _velocity;								//矢印の移動量
	EquipmentInfometion _data;

	void (MenuScene::*_update)();
	void MenuUpdate();

	void Draw();

	void TypeOfWeapons();

	void WeaponSelect();
	void ToolSelect();

	Vector2 ImageShaker(Rect& rect);

public:

	MenuScene();
	~MenuScene();

	bool Update();

};
