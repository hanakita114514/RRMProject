#pragma once
#include "Scene.h"

//�e�X�g�p
#include "HPBar.h"
#include "HitPoint.h"
#include "EffectManager.h"

class OfficialScene : public Scene
{
private:
	//�e�X�g
	HitPoint _hp;
	EffectManager _em;

public:
	OfficialScene();
	~OfficialScene();

	bool Update();
};

