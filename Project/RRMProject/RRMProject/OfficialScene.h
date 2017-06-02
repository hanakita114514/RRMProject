#pragma once
#include "Scene.h"

//テスト用
#include "HPBar.h"
#include "HitPoint.h"
#include "EffectManager.h"

class OfficialScene : public Scene
{
private:
	//テスト
	HitPoint _hp;
	EffectManager _em;

public:
	OfficialScene();
	~OfficialScene();

	bool Update();
};

