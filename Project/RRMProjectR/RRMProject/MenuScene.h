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

//Sîñi[p\¢Ì
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
	int _stageId;					//Xe[WID
	int _logoIdx;					//Logo\¢ÌzñÌY¦
	int _toolIdx;					//òÑ¹ïzñÌY¦
	int _weaponIdx;					//ízñÌY¦
	int _bg;						//wiÌænh
	float _freamCnt;
	bool _isInput;

	MenuInformation _menuInfo;
	LOGO _logo;

	Arrow _arrow;				//îó
	Input* _input;
	Vector2 _logoDefaultPos[(int)(LogoIdx::logoMax)];
	Vector2 _velocity;								//îóÌÚ®Ê
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
