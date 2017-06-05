#pragma once
#include "Scene.h"

//テスト用
#include "HPBar.h"
#include "HitPoint.h"

class OfficialScene : public Scene
{
private:
	//テスト
	HitPoint _hp;

public:
	OfficialScene();
	~OfficialScene();

	bool Update();
};

